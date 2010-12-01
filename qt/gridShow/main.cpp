/*
 * Date: 2010-11-10
 * yurenjimi@gmail.com
 *
 * Modify: 2010-12-01
 */
#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
