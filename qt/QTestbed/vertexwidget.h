#ifndef VERTEXWIDGET_H
#define VERTEXWIDGET_H

#include <QLabel>

class VertexWidget : public QLabel
{
    Q_OBJECT
public:
    explicit VertexWidget(QWidget *shapeWidget, QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QWidget *m_widget;
};

#endif // VERTEXWIDGET_H
