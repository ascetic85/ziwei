/*
 * 来自MeeGo 的example, 略修改
 */
#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QList>
#include <QSize>
#include <QPair>
#include <QDir>
#include <QPixmap>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QAbstractTableModel>

class Loader;

struct MediaType
{
    enum Type {
        Image = 0
    } type;

    QString path;
    QImage image;
};

Q_DECLARE_METATYPE(MediaType);

class GridModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Role {
        ImageId = Qt::UserRole + 1,
        Type
    };


    explicit GridModel(const QSize &size, const QStringList &dirs, int col, QObject *parent = 0);
    ~GridModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private slots:
    void insertImage(QImage pixmap, int index);

private:
    void createItems();
    QMap<int, QVariant> m_items;

    QList<Loader*> m_loaders;
    QStringList m_dirs;
    int m_col;
};

typedef QPair<QString, int> BacklogItem;

class Loader : public QThread
{
    Q_OBJECT
public:
    explicit Loader (const QSize &s)
        : QThread(), mutex(), haveWork(), backlog(), size(s), stopWork(false) { }
    void pushImage(const QString &path, int index);
    void stop();
    void scaleImage(QImage& image) const;

signals:
    void imageReady(QImage pixmap, int index);

protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition haveWork;
    QList<BacklogItem> backlog;
    QSize size;
    bool stopWork;
};

#endif // GRIDMODEL_H
