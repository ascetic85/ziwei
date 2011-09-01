#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = 0);

    void setCenter(const QPointF &center);
    void setAngle(qreal angle);

private:
    void updateCenter();

private:
    qreal m_angle;
    QPointF m_center;
};

#endif // GRAPHICSVIEW_H
