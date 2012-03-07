#ifndef VERTEXWIDGET_H
#define VERTEXWIDGET_H

#include <QLabel>

class VertexWidget : public QLabel
{
    Q_OBJECT
public:
    explicit VertexWidget(QWidget *shapeWidget, QWidget *parent = 0);
    void setVertex(QPoint p);
    QPoint vertex();
    
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    QWidget *m_widget;
    bool m_pressed;
    QPoint m_pressedPoint;
    QPoint m_vertex;
};

#endif // VERTEXWIDGET_H
