#include "widget.h"



Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    testIndex = 0;
    testSelection = 0;
    testCount = 0;
    width = 640;
    height = 480;
    framePeriod = 16;
    settingsHz = 60.0;
    viewZoom = 1.0f;
}

void Widget::initializeGL()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void Widget::resizeGL(int w, int h)
{
    width = w;
    height = h;

//    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float32 ratio = float32(tw) / float32(th);

    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = settings.viewCenter - extents;
    b2Vec2 upper = settings.viewCenter + extents;

    // L/R/B/T
    gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    test->SetTextLine(30);
//    b2Vec2 oldCenter = settings.viewCenter;
    settings.hz = settingsHz;
//    test->Step(&settings);
//    if (oldCenter.x != settings.viewCenter.x || oldCenter.y != settings.viewCenter.y)
//    {
//        Resize(width, height);
//    }

//    test->DrawTitle(5, 15, entry->name);

//    glutSwapBuffers();

    if (testSelection != testIndex)
    {
        testIndex = testSelection;
//        delete test;
//        entry = g_testEntries + testIndex;
//        test = entry->createFcn();
        viewZoom = 1.0f;
        settings.viewCenter.Set(0.0f, 20.0f);
//        Resize(width, height);
    }
}

b2Vec2 Widget::ConvertScreenToWorld(int32 x, int32 y)
{
    float32 u = x / float32(tw);
    float32 v = (th - y) / float32(th);

    float32 ratio = float32(tw) / float32(th);
    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = settings.viewCenter - extents;
    b2Vec2 upper = settings.viewCenter + extents;

    b2Vec2 p;
    p.x = (1.0f - u) * lower.x + u * upper.x;
    p.y = (1.0f - v) * lower.y + v * upper.y;
    return p;
}
