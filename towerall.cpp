#include "towerall.h"
#include "all.h"
#include "playscene.h"
TowerAll::TowerAll(QPoint pos, QString path, PlayScene *game) : TowerParent(pos,path,game)
{
    setDamage(5,10,15);
    //配置群攻音效
    allPlayer.setMedia(QUrl("qrc:/res/music/all.mp3"));
    allPlayer.setVolume(18);
}

void TowerAll::shootWeapon()
{
    allPlayer.play();//播放群攻音效
//All::All(QPoint position, int targetRadius, int damage, PlayScene *game)
        All *all=new All(TowerParent::getPos(),TowerParent::getAttackRange(),TowerParent::getDamage(),TowerParent::getGame());
        all->move();
        TowerParent::getGame()->addAll(all);

}

void TowerAll::levelUp()
{
    levelChange();
}
