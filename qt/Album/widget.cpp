#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "widget.h"
#include "graphicsview.h"
#include "gridview.h"

const int SCENE_WIDTH = 10000;
const int SCENE_HEIGHT = 10000;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_scene(0)
    , m_proxy(0)
    , m_viewTop(0)
    , m_viewCenter(0)
    , m_viewBottom(0)
{
    // Scene
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(-SCENE_WIDTH/2, -SCENE_HEIGHT/2, SCENE_WIDTH, SCENE_HEIGHT);

    // Item, proxy a Widget(GridView)
    m_proxy = new QGraphicsProxyWidget();
    GridView *gridView = new GridView(0);
    m_proxy->setWidget(gridView); // widget must be a top-level widget whose parent is 0.
    // Populate the item
    const QRectF r = m_proxy->rect();
    m_proxy->setPos(-r.width()/2, -r.height()/2);

    m_scene->addItem(m_proxy); // takes ownership

    // calculate X of view
    setFixedSize(360, 640);
    int x = (r.width() <= 360) ? (360 - r.width()) / 2 : 0;

    // ------------- View at center
    m_viewCenter = new GraphicsView(this);
    m_viewCenter->setScene(m_scene);
    m_viewCenter->setCenter(QPointF(0, 0));
    // size
    m_viewCenter->setGeometry(x, gridView->height()/2-50, gridView->width(), 100);

    // ------------- View on top
    int height = (gridView->height() - m_viewCenter->height()) / 2;
    int centerY = (gridView->height() - height) / 2;
    m_viewTop = new GraphicsView(this);
    m_viewTop->setScene(m_scene);
    m_viewTop->setCenter(QPointF(0, -centerY));
    m_viewTop->setAngle(30);
    // size
    m_viewTop->setGeometry(x, 0, gridView->width(), height);

    // ------------- View on bottom
    m_viewBottom = new GraphicsView(this);
    m_viewBottom->setScene(m_scene);
    m_viewBottom->setCenter(QPointF(0, centerY));
    m_viewBottom->setAngle(-30);
    // size
    m_viewBottom->setGeometry(x, gridView->height()/2+50, gridView->width(), height);
}

