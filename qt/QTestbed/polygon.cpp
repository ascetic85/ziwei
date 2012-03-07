#include "polygon.h"
#include <QPainter>
#include <QMouseEvent>
#include "vertexwidget.h"


Polygon::Polygon(QWidget *parent)
    : Shape(parent)
{
    addVertex(QPoint(0,0));
    addVertex(QPoint(100,0));
    addVertex(QPoint(100,200));
    addVertex(QPoint(0,100));
}

Polygon::~Polygon()
{
    qDeleteAll(m_vertexWidgets);
    m_vertexWidgets.clear();
}

void Polygon::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::red);
    p.drawPolygon(QPolygon(polygon));
}

void Polygon::addVertex(QPoint v)
{
    polygon.append(v);
    update();

    VertexWidget *w = new VertexWidget(this, parentWidget());
    w->setVertex(v);
    m_vertexWidgets.append(w);
    w->move(pos()+v);
    w->show();
    w->raise();
}

QSize Polygon::sizeHint() const
{
    return polygon.boundingRect().size();
}

bool Polygon::replaceVertex(QPoint orgin, QPoint newOne)
{
    bool ret = false;
    int index = polygon.indexOf(orgin);
    if (index >= 0 && index < polygon.size()) {
        polygon.replace(index, newOne);
        update();
        ret = true;
    }
    return ret;
}

/*
  添加一个顶点
 */
void Polygon::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton) {
        addVertex(ev->pos());
    }

    Shape::mouseReleaseEvent(ev);
}

void Polygon::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed) {
        foreach (VertexWidget *w, m_vertexWidgets) {
            w->move(w->pos() + ev->pos() - m_pressedPoint);
        }
    }

    Shape::mouseMoveEvent(ev);
}
