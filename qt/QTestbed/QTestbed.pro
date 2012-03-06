#-------------------------------------------------
#
# Project created by QtCreator 2012-03-02T15:04:30
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = QTestbed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    vertexwidget.cpp \
    canvas.cpp \
    shape.cpp \
    polygon.cpp

HEADERS  += mainwindow.h \
    widget.h \
    vertexwidget.h \
    canvas.h \
    shape.h \
    polygon.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
