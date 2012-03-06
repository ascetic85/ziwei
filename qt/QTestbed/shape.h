#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <QDebug>

class Shape : public QWidget
{
    Q_OBJECT
public:
    explicit Shape(QWidget *parent = 0);
    
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    QPoint m_pressedPoint;
    bool m_pressed;
};

#endif // SHAPE_H
