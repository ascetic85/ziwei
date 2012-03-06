#include "canvas.h"

#include "polygon.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    Polygon *p = new Polygon(this);
}
