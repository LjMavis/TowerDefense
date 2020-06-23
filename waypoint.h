#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class WayPoint
{
public:
    WayPoint(QPoint pos);//构造

    void setNextWayPoint(WayPoint *nextPoint);//重置下一个点
    void setPos(QPoint pos);
    WayPoint* nextWayPoint() const;
    const QPoint pos() const;

    void draw(QPainter *painter) const;//画出路径

private:
    QPoint		_pos;
    WayPoint *			_nextWayPoint;
};

#endif // WAYPOINT_H
