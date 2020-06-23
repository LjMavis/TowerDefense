#include "enemy.h"
#include <QVector2D>
#include <QtMath>
#include <QPainter>
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


Enemy::Enemy(WayPoint *startWayPoint,PlayScene *game,int Hp,qreal speed,int reward,QString path) : QObject(0)
{
    _active=false;
    _pos=startWayPoint->pos();
    _destinationWayPoint=startWayPoint->nextWayPoint();
    _maxHp=Hp;
    _currentHp=Hp;
    _walkingSpeed=speed;
    _game=game;
    _pic.load(path);
    _reward=reward;

}
//激活怪物
void Enemy::doActivate()
{
    _active = true;
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
    QPoint healthBarPoint = _pos + QPoint(-Health_Bar_Width / 2 , -25 - 2 * Health_Bar_Height);
    // 绘制红色方框，表示最大生命,固定大小不变
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, Health_Bar_Height));
    painter->drawRect(healthBarBackRect);
    // 绘制绿色方框，表示当前生命,受m_currentHp / m_maxHp的变化影响
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)_currentHp / _maxHp * Health_Bar_Width, Health_Bar_Height));
    painter->drawRect(healthBarRect);

    // 偏移坐标,由中心点到左上角
    static const QPoint offsetPoint(-50 / 2,-50 / 2);
    //painter->rotate(m_rotationSprite); //旋转，暂且不用

    // 绘制敌人
    painter->drawPixmap(_pos + offsetPoint, _pic);
//    if(ifDecelerated())
//    {
//        painter->setBrush(QColor(0,0,255));
//        painter->setOpacity(0.5);
//        painter->drawRect(_pos.x() + offsetPoint.x(), _pos.y() + offsetPoint.y(), 50, 50);
//    }
//    if(ifPoisoned())
//    {
//        painter->setBrush(QColor(128,0,128));
//        painter->setOpacity(0.5);
//        painter->drawRect(_pos.x() + offsetPoint.x(), _pos.y() + offsetPoint.y(), 50, 50);
//    }
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
    qreal movementSpeed = _walkingSpeed;
    QVector2D normalized(targetPoint - _pos);
    normalized.normalize();
    _pos = _pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
//	m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}
