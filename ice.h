#ifndef ICE_H
#define ICE_H

#include <QObject>
#include "bullet.h"
class Ice : public Bullet
{
    Q_OBJECT
//    Q_PROPERTY(QPoint _currentPos READ currentPos WRITE setCurrentPos)
public:
    Ice(QPoint startPos, QPoint targetPoint, int damage,qreal speed, Enemy *target,PlayScene *game);
private:
    qreal _speed;//减少的速度

signals:

private slots:
    void hitTarget();//击中敌人
};

#endif // ICE_H
