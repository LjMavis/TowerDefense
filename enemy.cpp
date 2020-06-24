#include "enemy.h"
#include <QVector2D>
#include <QtMath>
#include <QPainter>
#include <QTimer>
#include "towerparent.h"
#include "playscene.h"
//碰撞函数，非成员，用在move()中判断敌人是否到达航点
bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);
    if (distance <= radius1 + radius2)//圆心距离小于半径和，判断为碰撞
        return true;
    return false;
}


Enemy::Enemy(WayPoint *startWayPoint, PlayScene *game, int Hp, double speed, int reward, QString path) : QObject(0)
{
    _active=false;
    _freezed=false;
    _pos=startWayPoint->pos();
    _destinationWayPoint=startWayPoint->nextWayPoint();
    _maxHp=Hp;
    _currentHp=Hp;
    _walkingSpeed=speed;
    _currentSpeed=speed;
    _game=game;
    _pic.load(path);
    _reward=reward;
    _alled=false;

}
//激活怪物
void Enemy::doActivate()
{
    _active = true;
}
//被锁定攻击
void Enemy::getAttacked(TowerParent *tower){
    _attackedTowerList.push_back(tower);
}
//受到伤害
void Enemy::getDamage(int damage)
{
//	_game->audioPlayer()->playSound(LaserShootSound);//击中音效，先不做
    _currentHp -= damage;

    if (_currentHp <= 0)// 阵亡,需要移除
    {
//		_game->audioPlayer()->playSound(EnemyDestorySound);//死亡音效
        _game->awardGold(_reward);
        getRemoved();
    }
}
//被ice攻击到
void Enemy::getFreezed()
{
    //m_game->audioPlayer()->playSound(LaserShootSound);  //音效，先不做
    _freezed = true;
    _currentSpeed-=0.5;
    qDebug()<<"敌人被减速";
    QTimer::singleShot( 4000, this, SLOT(recoverSpeed()));
}
void Enemy::recoverSpeed()
{
    _currentSpeed = _walkingSpeed;
    _freezed = false;
}
void Enemy::setAlled(){
    _alled=true;
    QTimer::singleShot( 500, this, SLOT(recover()));
}
void Enemy::recover()
{
    _alled=false;
}
//死亡，移除
void Enemy::getRemoved()
{
    if (_attackedTowerList.empty()){return;}

    foreach (TowerParent *attacker, _attackedTowerList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    _game->removedEnemy(this);
}


//画出怪物
void Enemy::draw(QPainter *painter)
{
    //未激活，不画出
    if (!_active){ return; }

    static const int Health_Bar_Width = 50;   //血条长度
    static const int Health_Bar_Height = 5;   //血条高度
      //敌人图像大小是50

    painter->save();  //save()与restore()对应使用

    painter->setPen(Qt::NoPen);  //画笔风格

    // 绘制血条
    //血条左上角坐标
    QPoint healthBarPoint = _pos + QPoint(- Health_Bar_Width/2, -25 - 2 * Health_Bar_Height);
    // 绘制红色方框，表示最大生命,固定大小不变
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, Health_Bar_Height));
    painter->drawRect(healthBarBackRect);
    // 绘制绿色方框，表示当前生命,受m_currentHp / m_maxHp的变化影响
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)_currentHp / _maxHp * Health_Bar_Width, Health_Bar_Height));
    painter->drawRect(healthBarRect);

    // 偏移坐标,由中心点到左上角
//    static const QPoint offsetPoint(-50 / 2,-50 / 2);
    //painter->rotate(m_rotationSprite); //旋转，暂且不用

    // 绘制敌人
    painter->drawPixmap(_pos.x()-25,_pos.y()-28,50,56,_pic);
    if(ifFreezed())
    {
        painter->setBrush(QColor(0,0,250));
        painter->setOpacity(0.5);
        painter->drawRect(_pos.x()-25,_pos.y()-28,50,56);
    }
    if(ifAll())
    {
        painter->setBrush(QColor(120,210,20));
        painter->setOpacity(0.5);
        painter->drawRect(_pos.x()-25,_pos.y()-28,50,56);
    }
    painter->restore();
}

void Enemy::move()
{
    if (!_active)
        return;

    if (collisionWithCircle(_pos, 1, _destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            _pos = _destinationWayPoint->pos();
            _destinationWayPoint = _destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            _game->getLifeDamage();
            _game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = _destinationWayPoint->pos();
    // 未来:修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = _currentSpeed;
    QVector2D normalized(targetPoint - _pos);
    normalized.normalize();
    _pos = _pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
//	m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}
