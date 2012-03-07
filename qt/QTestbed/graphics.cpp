#include "graphics.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QUrl>

#include "qtpolygon.h"
#include "qtpoint.h"
#include <QDebug>

Graphics::Graphics(QWidget *parent)
    : QWidget(parent)
    , m_pressed(false)
    , m_pressedPolygon(0)
{
    setAcceptDrops(true);
    addPolygon();
    addPolygon();
}

void Graphics::addPolygon(QPoint p)
{
    Q_UNUSED(p);

    QtPolygon *polygon = new QtPolygon(this);
    m_polygons.push_back(polygon);
}

void Graphics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,m_bg);
    foreach (QtPolygon *polygon, m_polygons) {
        painter.drawPolygon(polygon->polygon());
    }
}

void Graphics::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        foreach (QtPolygon *polygon, m_polygons) {
            if (polygon->polygon().containsPoint(ev->pos(), Qt::OddEvenFill)) {
                m_pressed = true;
                m_pressedPoint = ev->pos();
                m_pressedPolygon = polygon;
                break;
            }
        }
    }
}

void Graphics::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed && m_pressedPolygon) {
        QVector<QtPoint*> &vector = m_pressedPolygon->points();
        QPoint delta = ev->pos() - m_pressedPoint;
        foreach (QtPoint *point, vector) {
            point->move(point->pos() + delta);
        }
        update();
        m_pressedPoint = ev->pos();
    }
}

void Graphics::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pressed = false;
    m_pressedPolygon = 0;

    if (ev->button() == Qt::RightButton) {
        foreach (QtPolygon *polygon, m_polygons) {
            if (polygon->polygon().containsPoint(ev->pos(), Qt::OddEvenFill)) {
                polygon->addVertex(ev->pos());
                break;
            }
        }
    }
}

void Graphics::dropEvent(QDropEvent *ev)
{
    qDebug() << ev->mimeData()->urls();
    QUrl url = ev->mimeData()->urls().at(0);
    m_bg.load(url.toLocalFile());
    update();
}

void Graphics::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->acceptProposedAction();
}
