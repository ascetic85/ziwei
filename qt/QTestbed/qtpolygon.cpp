#include "qtpolygon.h"
#include "qtpoint.h"

//double GetPointDistance(CPoint p1, CPoint p2)
//{
//    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
//}
//float GetNearestDistance(CPoint PA, CPoint PB, CPoint P3)
//{

//    //----------ͼ2--------------------
//    float a,b,c;
//    a=GetPointDistance(PB,P3);
//    if(a<=0.00001)
//        return 0.0f;
//    b=GetPointDistance(PA,P3);
//    if(b<=0.00001)
//        return 0.0f;
//    c=GetPointDistance(PA,PB);
//    if(c<=0.00001)
//        return a;//���PA��PB������ͬ�����˳������������ؾ���
//    //------------------------------

//    if(a*a>=b*b+c*c)//--------ͼ3--------
//        return b;      //����Ƕ۽Ƿ���b
//    if(b*b>=a*a+c*c)//--------ͼ4-------
//        return a;      //����Ƕ۽Ƿ���a

//    //ͼ1
//    float l=(a+b+c)/2;     //�ܳ���һ��
//    float s=sqrt(l*(l-a)*(l-b)*(l-c));  //���׹�ʽ�������Ҳ������ʸ����
//    return 2*s/c;
//}


QtPolygon::QtPolygon(QWidget *w, QObject *parent)
    : QObject(parent)
    , m_parent(w)
{
    addVertex(QPoint(0,0));
    addVertex(QPoint(100,0));
    addVertex(QPoint(100,100));
    addVertex(QPoint(0,100));
}

QPolygon QtPolygon::polygon()
{
    QPolygon polygon;
    foreach (QtPoint *w, m_points) {
        polygon.push_back(w->pos());
    }

    return polygon;
}

QVector<QtPoint *> &QtPolygon::points()
{
    return m_points;
}

/*
 * �ҵ������@point �������
 */
void QtPolygon::addVertex(QPoint point)
{
    QtPoint *w = new QtPoint(m_points.size(), m_parent);
    connect(w, SIGNAL(deleteMe(int)), this, SLOT(deleteVertex(int)));
    // CODE here
    m_points.push_back(w);

    w->move(point);
    w->show();
    m_parent->update();
}

void QtPolygon::deleteVertex(int index)
{
    if ((index < m_points.size()) && m_points.size() > 3) {
        QtPoint *p = m_points.at(index);
        delete p;
        m_points.remove(index);
        m_parent->update();
        for (int i = 0; i < m_points.size(); i++) {
            m_points.at(i)->updateId(i);
        }
    }
}
