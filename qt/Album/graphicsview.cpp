#include <QGraphicsProxyWidget>
#include <math.h>

#include <QDebug>

#include "graphicsview.h"

const qreal PI = 3.1415926535897932384626433832795;

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setStyleSheet("QGraphicsView { border-style: none; }");
    setRenderHints(renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsView::setCenter(const QPointF &center)
{
    m_center = center;
    centerOn(m_center);
}

void GraphicsView::setAngle(qreal angle)
{
    m_angle = angle;

    updateCenter();
}

void GraphicsView::updateCenter()
{
    qreal dy = m_center.y() * (1/cos(PI*m_angle/180.0) - 1) * 1.35; // 1.35 is related to m_angle...
    m_center.setY(m_center.y() + dy);
    centerOn(m_center);
    setTransform(QTransform().rotate(m_angle, Qt::XAxis));

    this->scale(1.025, 1.025); // 1.025 is related to m_angle...
}
