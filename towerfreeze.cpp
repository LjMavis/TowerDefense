#include "towerfreeze.h"
#include "ice.h"
#include "playscene.h"
TowerFreeze::TowerFreeze(QPoint pos, QString path, PlayScene *game) : TowerParent(pos,path,game)
{
    _speed = 1.0;
//    setDamage(5,15,20);
}

void TowerFreeze::shootWeapon(){
    shootPlayer.play();//播放射击音效
//    Ice(QPoint startPos, QPoint targetPoint, int damage,qreal speed, Enemy *target,PlayScene *game);
    Ice *ice = new Ice(TowerParent::getPos(), TowerParent::getTargetEnemy()->getPos(),TowerParent::getDamage(),_speed, TowerParent::getTargetEnemy(),TowerParent::getGame());
    ice->move();
    TowerParent::getGame()->addIce(ice);
}
void TowerFreeze::levelUp()
{
    levelChange();
}
