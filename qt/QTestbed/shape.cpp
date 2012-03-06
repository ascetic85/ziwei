#include "shape.h"
#include <QMouseEvent>

Shape::Shape(QWidget *parent)
    : QWidget(parent)
    , m_pressed(false)
{
}

void Shape::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        m_pressedPoint = ev->pos();
        ev->accept();
    }
}

void Shape::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed) {
        move(pos() + ev->pos() - m_pressedPoint);
    }
}

void Shape::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = false;
    }
}
