#include "towerfreeze.h"
#include "ice.h"

TowerFreeze::TowerFreeze(QPoint pos, QString path, PlayScene *game) : TowerParent(pos,path,game)
{
    _speed = 1.0;
//    setDamage(5,15,20);
}

void TowerFreeze::shootWeapon(){
//    m_player2.play();//发射子弹的音效，暂时不做
//    Ice(QPoint startPos, QPoint targetPoint, int damage,qreal speed, Enemy *target,PlayScene *game);
    Ice *ice = new Ice(TowerParent::getPos(), TowerParent::getTargetEnemy()->getPos(),TowerParent::getDamage(),_speed, TowerParent::getTargetEnemy(),TowerParent::getGame());
    ice->move();
    TowerParent::getGame()->addIce(ice);
}
