#ifndef QTPOINT_H
#define QTPOINT_H

#include <QLabel>
#include <QPoint>
#include <QDebug>

class QtPoint : public QLabel
{
    Q_OBJECT
public:
    explicit QtPoint(int m_id, QWidget *parent);

    void updateId(int id);

signals:
    void deleteMe(int m_id);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void keyReleaseEvent(QKeyEvent *);

private:
    bool m_pressed;
    QPoint m_pressedPoint;
    int m_id;
};

#endif // QTPOINT_H
