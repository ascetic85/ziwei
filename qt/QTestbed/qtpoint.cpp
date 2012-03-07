#include "qtpoint.h"

#include <QPixmap>
#include <QBitmap>
#include <QMouseEvent>
#include <QMetaType>
#include <QKeyEvent>

QtPoint::QtPoint(int id, QWidget *parent)
    : QLabel(parent)
    , m_pressed(false)
    , m_id(id)
{
//    qRegisterMetaType<QtPoint*>("QtPoint*");
//    qRegisterMetaType<QList<RESPONSE_QUERY_RESULT_FILE> >("QList<RESPONSE_QUERY_RESULT_FILE>");
    QPixmap pixmap(":/img/v.bmp");
    setPixmap(pixmap);
    setMask(pixmap.mask());
}

void QtPoint::updateId(int id)
{
    m_id = id;
}

void QtPoint::mousePressEvent(QMouseEvent *ev)
{
    setFocus();
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        m_pressedPoint =  ev->pos();
    }
}

void QtPoint::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed) {
        move(pos() + ev->pos() - m_pressedPoint);
        parentWidget()->update();
    }
}

void QtPoint::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
}

void QtPoint::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Delete) {
        emit deleteMe(m_id);
    }
}
