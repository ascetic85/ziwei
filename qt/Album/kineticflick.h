#ifndef KINETICFLICK_H
#define KINETICFLICK_H

#include <QPointF>
#include <QGraphicsWidget>
#include <QObject>

class KineticFlickPrivate;

class KineticFlick : public QObject
{
    Q_OBJECT

public:
    KineticFlick(QObject *parent = 0);
    ~KineticFlick();
    void activateOn(QWidget *widget);


public Q_SLOTS:
    void kineticMove(int);

protected:
    //KineticFlick(KineticFlickPrivate &dptr, QGraphicsItem *parent = 0);
    void deactivateFrom(QWidget *widget);
    bool eventFilter(QObject *object, QEvent *event);
    void modelChanged();


private:
    KineticFlickPrivate *d;
    friend class KineticFlickPrivate;
};

#endif
