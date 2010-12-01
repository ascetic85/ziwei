#include "widget.h"

#include <QFileSystemModel>
#include <QDebug>
#include "griddelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_view(0)
{
    m_view = new QTableView(this);
//    m_view->setShowGrid(false);
//    m_view->horizontalHeader()->hide();
//    m_view->verticalHeader()->hide();
//    m_view->horizontalHeader()->setMinimumSectionSize(1);
//    m_view->verticalHeader()->setMinimumSectionSize(1);

    // Delegate
    GridDelegate *delegate = new GridDelegate(this);
    m_view->setItemDelegate(delegate);

    // Mode
    QStringList dirs;
    dirs << "/home/jryin/Pictures/f";
    GridModel *model = new GridModel(QSize(100, 100), dirs, 4, this);
    m_view->setModel(model);


    m_view->resizeColumnsToContents();
    m_view->resizeRowsToContents();

    resize(640, 480);
    m_view->resize(this->size());

    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(ItemClick(QModelIndex)));
}

Widget::~Widget()
{
}

void Widget::ItemClick(QModelIndex index)
{
    MediaType m = index.data(Qt::DisplayRole).value<MediaType>();
    QLabel *label = new QLabel(this);
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->setPixmap(QPixmap::fromImage(m.image));
    label->show();
}
