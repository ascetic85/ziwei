#include <QHeaderView>
#include <QFileDialog>

#include <QDebug>

#include "gridview.h"
#include "gridmodel.h"
#include "griddelegate.h"
#include "flickcharm.h"
#include "kineticflick.h"

GridView::GridView(QWidget *parent)
    : QTableView(parent)
{
    qDebug() << __FILE__ << __LINE__ << ": Please set image dir in GridView::GridView()...";

    // Model
    QStringList dirs;
//    dirs << "D:/Images/image/";
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        dirs << dialog.selectedFiles();

    GridModel *model = new GridModel(QSize(100, 100), dirs, 3, this);
    setModel(model);

    // Delegate
    GridDelegate *delegate = new GridDelegate(this);
    setItemDelegate(delegate);

    // View
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    resize(306, 640);
    // Works with sizeHint() in delegate
    resizeColumnsToContents();
    resizeRowsToContents();

    // Kinetic...
#if 0
    // 1. FlickCharm from Qt libs dojo (not good enough)
    FlickCharm *flick = new FlickCharm(this);
    flick->activateOn(this);
#else
    // 2. KineticFlick by Yan Xu
    KineticFlick *flick = new KineticFlick(this);
    flick->activateOn(this);
#endif

    setStyleSheet("QTableView { border-style: none; }");
}
