#include "towerparent.h"
#include <QString>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "qmath.h"
#include "playscene.h"
#include "bullet.h"

TowerParent::TowerParent(QPoint pos,QString path,PlayScene *game)
{
    _level=0;
    _pos = pos;
    _range[0]=80;_range[1]=110;_range[2]=130;
    _damage[0]=10;_damage[1]=15;_damage[2]=20;
    _cd[0]=1500;_cd[1]=1200;_cd[2]=900;
    TowerPath = path;
    _w=45;
    _h=45;
    _targetEnemy = NULL;
    _game = game;
//    m_game2 = NULL;
    _fireRateTimer = new QTimer(this);
    connect(_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()) );
//    m_player.setMedia(QUrl("qrc:/pic/music/towersound.mp3"));
//    m_player.setVolume(30);
}

TowerParent::~TowerParent()
{
    delete _fireRateTimer;
    _fireRateTimer = NULL;
}
QPoint TowerParent::getPos(){
    return this->_pos;
}

void TowerParent::attack()
{
//    _fireRateTimer->start(_cd[_level]);
//    qDebug()<<"启动_fireRateTimer";
}
void TowerParent::attackEnemy(Enemy *enemy)//启动攻击
{
    _targetEnemy = enemy;
    qDebug()<<"设置了攻击对象";

    shootWeapon();//因为_fireRateTimer->start(_cd[_level])会在_cd[_level]时间后才开始攻击，所以手动补上第一次攻击
    _fireRateTimer->start(_cd[_level]);
    attack();
    _targetEnemy->getAttacked(this);

}


//bool collisionWithCircle1(QPoint point1, int radius1, QPoint point2, int radius2)
//{
//    const int xdif = point1.x() - point2.x();
//    const int ydif = point1.y() - point2.y();
//    const int distance = qSqrt(xdif * xdif + ydif * ydif);
//    if (distance <= radius1 + radius2)//圆心距离小于半径和，判断为碰撞
//        return true;
//    return false;
//}
//void TowerParent::checkEnemyInRange()
//{
//    if (_targetEnemy)
//    {
////		// 这种情况下,需要旋转炮台对准敌人
////		// 向量标准化
////		QVector2D normalized(m_chooseEnemy->pos() - m_pos);
////		normalized.normalize();
////		m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

//        // 如果敌人脱离攻击范围
//        if (!collisionWithCircle1(_pos, _range[_level], _targetEnemy->getPos(), 1))
//            loseEnemy();
//    }
//    else
//    {
//        // 遍历敌人,看是否有敌人在攻击范围内
//        QList<Enemy *> enemyList = _game->enemyList();
//        foreach (Enemy *enemy, enemyList)
//        {
//            if (collisionWithCircle1(_pos, _range[_level], enemy->getPos(), 1))
//            {
//                attackEnemy(enemy);
//                break;
//            }
//        }
//    }
//}

void TowerParent::shootWeapon()//每次攻击产生一个子弹，由PlayScene管理
{
    Bullet *bullet = new Bullet(_pos, _targetEnemy->getPos(), _damage[_level], _targetEnemy,_game);
    bullet->move();
    _game->addBullet(bullet);
}

void TowerParent::targetKilled()
{
    // 目标死亡时,也需要取消关联
    // 取消攻击
    if (_targetEnemy)
        _targetEnemy = NULL;
    _fireRateTimer->stop();
    //m_rotationSprite = 0.0;
}

void TowerParent::loseEnemy()
{
    // 当敌人脱离炮塔攻击范围,要将炮塔攻击的敌人关联取消
    // 同时取消攻击
    _targetEnemy = NULL;
    _fireRateTimer->stop();
    //m_rotationSprite = 0.0;
}

void TowerParent::draw(QPainter *painter){
    painter->save();
    painter->setPen(Qt::white);// 绘制攻击范围
    painter->drawEllipse(_pos.x()+25-_range[_level],_pos.y()+25-_range[_level],_range[_level]*2,_range[_level]*2);
    // 尺寸大小派上用场了,当然也可以直接获取图片大小,是一样的
//    static const QPoint offsetPoint(-40,-40);
    // 绘制炮塔并选择炮塔
    // 这里将坐标原点移到m_pos,绘制的适合,就要加上那个偏移点到左上角
//    painter->translate(_pos);
    QPixmap pix;
    bool ret=(pix.load(TowerPath));
    if(!ret){
        qDebug()<<"加载图片出错";
    }
    painter->drawPixmap(_pos.x()+25-_w/2,_pos.y()+25-_h/2,_w,_h,pix);
    painter->restore();
}
void TowerParent::levelUp()
{
    _level ++;
    _w+=10;
    _h+=10;
}
