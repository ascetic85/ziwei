#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QGraphicsScene;
class QGraphicsProxyWidget;
class GraphicsView;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:

public slots:

private:
    QGraphicsScene *m_scene;
    QGraphicsProxyWidget *m_proxy;
    GraphicsView *m_viewTop;
    GraphicsView *m_viewCenter;
    GraphicsView *m_viewBottom;
};

#endif // WIDGET_H
