#include "griddelegate.h"

#include <QPainter>
#include <QTableWidgetItem>
#include <QDebug>
GridDelegate::GridDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void GridDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if (option.state & QStyle::State_Selected)
//        painter->fillRect(option.rect, option.palette.highlight());

    MediaType m = index.data(Qt::DisplayRole).value<MediaType>();
    if (m.type == MediaType::Image) {
        QRect rect = option.rect;
        qDebug() << rect;
        painter->drawImage(rect, m.image);
    }
}

QSize GridDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(100, 100);
}
