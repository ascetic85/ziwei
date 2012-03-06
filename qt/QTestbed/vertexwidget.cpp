#include "vertexwidget.h"
#include <QPixmap>
#include <QBitmap>

#include <QDebug>

const QString vertexPng("./img/v.bmp");

VertexWidget::VertexWidget(QWidget *shapeWidget, QWidget *parent)
    : QLabel(parent)
    , m_widget(shapeWidget)
{
    QPixmap p(vertexPng);
    setPixmap(p);
    setMask(QBitmap(p));
}
