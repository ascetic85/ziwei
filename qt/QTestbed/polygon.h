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
    bool replaceVertex(QPoint orgin, QPoint newOne);

    QPolygon polygon;

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    void addVertex(QPoint v);

private:

    QList<VertexWidget*> m_vertexWidgets;
};

#endif // POLYGON_H
