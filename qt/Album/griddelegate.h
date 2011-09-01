#ifndef GRIDDELEGATE_H
#define GRIDDELEGATE_H

#include <QStyledItemDelegate>

class GridDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    GridDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // GRIDDELEGATE_H
