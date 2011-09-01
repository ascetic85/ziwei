#include <QScrollBar>
#include <QDebug>
#include <QAbstractScrollArea>

#include "kineticflick.h"
#include "kineticscroll.h"

class KineticFlickPrivate
{
public:
    KineticFlickPrivate(KineticFlick *qptr);

    bool isClickPossible(int y);
    int getPosSmooth(int y);
    bool moveOffset(int offset);
    bool dragging;
    bool mouseDown;
    int actualPosY;
    int mouseDownPos;
    int moveConstant;
    int clickConstant;
    double clickInitTime;
    double clickBlockTime;
    KineticScroll *kinetic;
    QWidget *widget;
    QPoint offset;
private:

};

static QPoint scrollOffset(QWidget *widget)
{
    int x = 0, y = 0;

    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        x = scrollArea->horizontalScrollBar()->value();
        y = scrollArea->verticalScrollBar()->value();
    }
    return QPoint(x, y);
}

static void setOffset(QWidget *widget, int value)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        scrollArea->verticalScrollBar()->setValue(value);
    }
}
KineticFlickPrivate::KineticFlickPrivate(KineticFlick *qptr)
    : kinetic(0)
{
    dragging = false;
    moveConstant = 15;
    clickConstant = 20;
    clickInitTime = 0.4;
    clickBlockTime = 0.5;
    actualPosY = -1;
    mouseDownPos = -1;
    offset = QPoint(0,0);
}


bool KineticFlickPrivate::isClickPossible(int y)
{
    if (dragging || mouseDownPos < 0)
        return false;
    else
        return abs(y - mouseDownPos) <= clickConstant;
}

int KineticFlickPrivate::getPosSmooth(int y)
{
    if (abs(mouseDownPos - y) <= moveConstant)
        return y;
    else if (mouseDownPos - y < 0)
        return y - moveConstant;
    else
        return y + moveConstant;
}

bool KineticFlickPrivate::moveOffset(int value)
{

    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        offset = scrollOffset(widget);
    int finalOffset = offset.y() - value;

    setOffset(widget,finalOffset);

}

    return true;
}



KineticFlick::KineticFlick(QObject *parent)
    : QObject(parent)
{
    d = new KineticFlickPrivate(this) ;
    d->kinetic = new KineticScroll(this);
    connect(d->kinetic, SIGNAL(signalMoveOffset(int)), SLOT(kineticMove(int)));
}


void KineticFlick::activateOn(QWidget *widget)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QWidget *viewport = scrollArea->viewport();

        viewport->installEventFilter(this);
        scrollArea->installEventFilter(this);
        d->widget = widget;

        return;
    }
}


bool KineticFlick::eventFilter(QObject *object, QEvent *event)
{
    if (!object->isWidgetType())
        return false;

    QEvent::Type type = event->type();
    if (type != QEvent::MouseButtonPress &&
            type != QEvent::MouseButtonRelease &&
            type != QEvent::MouseMove)
        return false;

    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (!mouseEvent || mouseEvent->modifiers() != Qt::NoModifier)
        return false;

    QWidget *viewport = dynamic_cast<QWidget*>(object);
    if (!viewport)
       return false;

    bool consumed = false;
    switch(type)
    {
    case QEvent::MouseButtonPress:
        {
            int y = mouseEvent->pos().y();
            d->mouseDownPos = y;
            d->dragging = !d->kinetic->mouseDown(y);
            d->actualPosY = y;
            d->mouseDown = true;
            consumed = true;
            d->offset = scrollOffset(d->widget);
        }
    case QEvent::MouseButtonRelease:
        {
            d->mouseDown = false;
            if (d->mouseDownPos >= 0) {
                int y = mouseEvent->pos().y();
                if (d->isClickPossible(y)) {
                    //Todo

                } else {
                    d->kinetic->mouseUp(d->getPosSmooth(y));
                }
            }
            d->offset = scrollOffset(d->widget);
            consumed = true;

        }
    case QEvent::MouseMove:
        {
            if (d->mouseDownPos >= 0) {
                int y = mouseEvent->pos().y();
                d->actualPosY = y;

                if (!d->isClickPossible(y)) {
                    d->dragging = true;
                }

                if (abs(d->mouseDownPos - y) > d->moveConstant)
                    d->kinetic->mouseMove(d->getPosSmooth(y));
            }
            consumed = true;

        }
    default:
        consumed = false;
        break;

    }

return consumed;

}

KineticFlick::~KineticFlick()
{

}

void KineticFlick::kineticMove(int value)
{
    d->moveOffset(value);
}


void KineticFlick::modelChanged()
{
    d->kinetic->kineticStop();

}
