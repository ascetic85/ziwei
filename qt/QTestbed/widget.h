#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QWidget>
#include <QtOpenGL/QGLWidget>

#include "Box2D/Box2D.h"
#include "gl/glu.h"
//#include "gl/glut.h"

/// Test settings. Some can be controlled in the GUI.
struct Settings
{
    Settings() :
        viewCenter(0.0f, 20.0f),
        hz(60.0f),
        velocityIterations(8),
        positionIterations(3),
        drawShapes(1),
        drawJoints(1),
        drawAABBs(0),
        drawPairs(0),
        drawContactPoints(0),
        drawContactNormals(0),
        drawContactForces(0),
        drawFrictionForces(0),
        drawCOMs(0),
        drawStats(0),
        drawProfile(0),
        enableWarmStarting(1),
        enableContinuous(1),
        enableSubStepping(0),
        pause(0),
        singleStep(0)
        {}

    b2Vec2 viewCenter;
    float32 hz;
    int32 velocityIterations;
    int32 positionIterations;
    int32 drawShapes;
    int32 drawJoints;
    int32 drawAABBs;
    int32 drawPairs;
    int32 drawContactPoints;
    int32 drawContactNormals;
    int32 drawContactForces;
    int32 drawFrictionForces;
    int32 drawCOMs;
    int32 drawStats;
    int32 drawProfile;
    int32 enableWarmStarting;
    int32 enableContinuous;
    int32 enableSubStepping;
    int32 pause;
    int32 singleStep;
};


class Widget : public QGLWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    b2Vec2 ConvertScreenToWorld(int32 x, int32 y);

private:
    int32 testIndex;
    int32 testSelection;
    int32 testCount;
//    TestEntry* entry;
//    Test* test;
    Settings settings;
    int32 width;
    int32 height;
    int32 framePeriod;
    int32 mainWindow;
    float settingsHz;
//    GLUI *glui;
    float32 viewZoom;
    int tx, ty, tw, th;
    bool rMouseDown;
    b2Vec2 lastp;
};

#endif // WIDGET_H
