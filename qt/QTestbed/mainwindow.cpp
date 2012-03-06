#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include "canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("QTestbed");
    ui->setupUi(this);

//    Widget *w = new Widget(this);
//    setCentralWidget(w);
    Canvas *w = new Canvas(this);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}
