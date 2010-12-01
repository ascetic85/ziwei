#include "gridmodel.h"

#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

#define THREAD_COUNT 5

GridModel::GridModel(const QSize &size, const QStringList &dirs,
                     int col, QObject *parent)
    : QAbstractTableModel(parent),
      m_dirs(dirs),
      m_col(col)
{
    qRegisterMetaType<MediaType>("MediaType");

    for (int i = 0; i < THREAD_COUNT; i++) {
        Loader *loader = new Loader(size);
        loader->start(QThread::LowestPriority);
        connect(loader, SIGNAL(imageReady(QImage, int)), this, SLOT(insertImage(QImage, int)));
        m_loaders.append(loader);
    }

    createItems();
}

GridModel::~GridModel()
{
    for (int i = 0; i < THREAD_COUNT; i++) {
        Loader *loader = m_loaders[i];
        loader->stop();
        loader->wait();
    }
    qDeleteAll(m_loaders);
    m_loaders.clear();
}

int GridModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int row = m_items.size()/m_col;
    if (m_items.size()%m_col)
        row += 1;
    return row;
}

int GridModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_col;
}

QVariant GridModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.isValid());
    Q_ASSERT(index.row() < m_items.size());

    MediaType m;
    int id = index.row() * m_col + index.column();

    if (m_items[ id ].canConvert<MediaType>())
        m = m_items[ id ].value<MediaType>();

    if (role == Qt::DisplayRole)
        return m_items[id];
    else if (role == GridModel::Type)
        return m.type;
    else if (role == GridModel::ImageId)
        return m.path;

    return QVariant();
}

void GridModel::createItems()
{
    int index = 0;

    foreach (const QString &dir, m_dirs) {
        QDir mediaDir(dir);
        mediaDir.setFilter(QDir::Files | QDir::NoSymLinks);
        mediaDir.setSorting(QDir::Name);
        mediaDir.setNameFilters(QStringList() << "*.jpeg" << "*.jpg" << "*.png");
        const QFileInfoList fileList = mediaDir.entryInfoList();

        foreach (const QFileInfo & file, fileList) {
            const QString path = file.absoluteFilePath();
            MediaType m;

            m.type = MediaType::Image;
            m.path = path;
            m.image = QImage();
            Loader *loader = m_loaders[index % THREAD_COUNT];
            loader->pushImage(path,index);

            m_items[index] = QVariant::fromValue(m);
            index++;
        }
    }
}

void GridModel::insertImage(QImage image, int index)
{
    if (m_items[index].canConvert<MediaType>()) {
        MediaType m = m_items[index].value<MediaType>();
        m.image = image;
        m_items[index] = QVariant::fromValue(m);

        int row = index / m_col;
        int col = index % m_col;

//        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        emit dataChanged(createIndex(row, col), createIndex(row, col));
    }
}

void Loader::run()
{
    while (true) {
        mutex.lock();
        if (stopWork) {
            mutex.unlock();
            return;
        }
        if (backlog.isEmpty()) {
            haveWork.wait(&mutex);
            mutex.unlock();
            continue;
        }

        BacklogItem backlogItem = backlog.takeFirst();
        mutex.unlock();
        const QFileInfo file(backlogItem.first);
        int index = backlogItem.second;

        QImage image(file.absoluteFilePath());

        if (!image.isNull()) {
            scaleImage(image);
            emit imageReady(image, index);
        }
    }
}

void Loader::scaleImage(QImage& image) const
{
    image = image.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    if (image.size() != size) {
        QPoint start((image.width() - size.width()) / 2, (image.height() - size.height()) / 2);
        image = image.copy(QRect(start, size));
    }
}

void Loader::pushImage(const QString &path, int index)
{
    BacklogItem backlogItem(path, index);
    mutex.lock();

    backlog.append(backlogItem);
    mutex.unlock();
    haveWork.wakeAll(); // Important
}

void Loader::stop()
{
    mutex.lock();
    stopWork = true;
    haveWork.wakeAll();
    mutex.unlock();
}
