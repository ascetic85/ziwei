#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>

class VertexWidget;
class QtPolygon;

class Graphics : public QWidget
{
    Q_OBJECT
public:
    explicit Graphics(QWidget *parent = 0);

    void addPolygon(QPoint p = QPoint());

protected:
    void paintEvent(QPaintEvent *);

    /* ÍÏ¶¯ */
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent *);

private:
    QVector<QtPolygon*> m_polygons;

    bool m_pressed;
    QPoint m_pressedPoint;
    QtPolygon *m_pressedPolygon;

    QPixmap m_bg;
};

#endif // GRAPHICS_H
