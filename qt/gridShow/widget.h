#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui>

#include "gridmodel.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void ItemClick(QModelIndex index);

private:
    QTableView *m_view;
};

#endif // WIDGET_H
