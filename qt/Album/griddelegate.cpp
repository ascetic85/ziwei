#include <QPainter>

#include "griddelegate.h"
#include "gridmodel.h"

GridDelegate::GridDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void GridDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    MediaType m = index.data(Qt::DisplayRole).value<MediaType>();
    if (m.type == MediaType::Image) {
        QRect rect = option.rect;

        painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
        painter->drawImage(rect, m.image);
    }
}

QSize GridDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(100, 100);
}
