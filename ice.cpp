#include "ice.h"
#include "enemy.h"
#include "playscene.h"

#include <QAnimationDriver>
#include <QPropertyAnimation>
#include <QList>

Ice::Ice(QPoint startPos, QPoint targetPoint, int damage, qreal speed, Enemy *target, PlayScene *game) : Bullet(startPos,targetPoint,damage,target,game)
{
    setPix(":/res/bullet3.png");
    _speed=speed;
}
void Ice::hitTarget()//击中目标
{
    // 先判断下敌人是否还有效
    if (getGame()->enemyList().indexOf(getTargetEnemy()) != -1){
        getTargetEnemy()->getDamage(getDamage());//目标受到伤害
        if((!getTargetEnemy()->ifFreezed())&&getTargetEnemy()->ifAlive())//目标未被减速并且还活着
        {
            getTargetEnemy()->getFreezed();
        }
    }
    getGame()->removedIce(this);
}
