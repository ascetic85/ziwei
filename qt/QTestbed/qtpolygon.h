#ifndef QTPOLYGON_H
#define QTPOLYGON_H

#include <QObject>
#include <QPolygon>
#include <QWidget>

class QtPoint;

class QtPolygon : public QObject
{
    Q_OBJECT
public:
    explicit QtPolygon(QWidget *w, QObject *parent = 0);

    void addVertex(QPoint point);
    QPolygon polygon();
    QVector<QtPoint*> & points();

private slots:
    void deleteVertex(int index);

private:
    QVector<QtPoint*> m_points;
    QWidget *m_parent;
};

#endif // QTPOLYGON_H
