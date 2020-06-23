#include "waypoint.h"

#include <QPen>
#include <QPainter>

WayPoint::WayPoint(QPoint pos):_pos(pos),_nextWayPoint(NULL){
}

void WayPoint::setNextWayPoint(WayPoint *nextPoint)
{
    _nextWayPoint = nextPoint;
}

void WayPoint::setPos(QPoint pos){
    _pos = pos;
}

WayPoint* WayPoint::nextWayPoint() const
{
    return _nextWayPoint;
}

const QPoint WayPoint::pos() const
{
    return _pos;
}

void WayPoint::draw(QPainter *painter) const
{
    painter->save();
    QPen pen = painter->pen();
    pen.setWidth(30);//改变线宽
    painter->setPen(pen);
    painter->setPen(QColor(119, 155, 23));//设置颜色
    painter->drawEllipse(_pos, 14, 14);
    painter->drawEllipse(_pos, 7, 7);

    if (_nextWayPoint){
        painter->drawLine(_pos, _nextWayPoint->_pos);
    }
    painter->restore();
}
