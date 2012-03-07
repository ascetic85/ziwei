#include "vertexwidget.h"
#include <QPixmap>
#include <QBitmap>
#include <QMouseEvent>
#include <QDebug>
#include "polygon.h"

const QString vertexPng("./img/v.bmp");

VertexWidget::VertexWidget(QWidget *shapeWidget, QWidget *parent)
    : QLabel(parent)
    , m_widget(shapeWidget)
    , m_pressed(false)
{
    QPixmap p(vertexPng);
    setPixmap(p);
    setMask(QBitmap(p));
}

void VertexWidget::setVertex(QPoint p)
{
    m_vertex = p;
}

QPoint VertexWidget::vertex()
{
    return m_vertex;
}

void VertexWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        m_pressedPoint = ev->pos();
        ev->accept();
    }
}

void VertexWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed) {
        Polygon *p = static_cast<Polygon*>(m_widget);
        if (p) {
            if (p->replaceVertex(m_vertex, pos() + ev->pos()-p->pos())) {
                m_vertex = pos() + ev->pos() - p->pos();
            }
        }

        // Move myself
        move(pos() + ev->pos() - m_pressedPoint);
    }
}

void VertexWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pressed = false;
}
