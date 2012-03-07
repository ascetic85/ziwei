#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include "canvas.h"
#include "graphics.h"
#include <QScrollArea>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("QTestbed");
    ui->setupUi(this);

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));

//    Widget *w = new Widget(this);
    Graphics *w = new Graphics(this);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "untitled.json",
                               tr("JSon (*.json)"));
    if (!fileName.isEmpty()) {

    }
}
