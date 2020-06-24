#include "towerall.h"
#include "all.h"
TowerAll::TowerAll(QPoint pos, QString path, PlayScene *game) : TowerParent(pos,path,game)
{
    setDamage(5,10,15);
}

void TowerAll::shootWeapon()
{
//    m_player2.play();
//All::All(QPoint position, int targetRadius, int damage, PlayScene *game)
        All *all=new All(TowerParent::getPos(),TowerParent::getAttackRange(),TowerParent::getDamage(),TowerParent::getGame());
        all->move();
        TowerParent::getGame()->addAll(all);

}
