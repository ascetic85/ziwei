#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QList>
class VertexWidget;

class Polygon : public Shape
{
    Q_OBJECT
public:
    Polygon(QWidget *parent = 0);
    ~Polygon();

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    void addVertex(QPoint v);

private:
    QPolygon m_polygon;
    QList<VertexWidget*> m_vertexWidgets;
};

#endif // POLYGON_H
