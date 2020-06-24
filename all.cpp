#include "all.h"
#include "enemy.h"
#include "playscene.h"

#include <QAnimationDriver>
#include <QPropertyAnimation>
#include <QList>

All::All(QPoint position, int targetRadius, int damage, PlayScene *game)
    : _game(game)
    , _damage(damage)
    , _pos(position+QPoint(25,25))
    , _targetRadius(targetRadius)
{
    _currentRadius = 0;
}

void All::move()
{
    static const int duration = 500;//存放动画持续时间（在500毫秒内击中敌人）

    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentRadius");
    animation->setDuration(duration);//设置持续时间
    animation->setStartValue(0);//设置初始半径
    animation->setEndValue(_targetRadius);//设置目标半径

    connect(animation, SIGNAL(finished()),this,SLOT(hitTarget()));//动画结束触发hitTarget()
    animation->start();
}
void All::hitTarget()//击中目标
{
    _game->allEffect(this);
}

void All::draw(QPainter *painter)
{
    painter->save();

    painter->setPen(QColor(40,120,41));
    QPen pen = painter->pen();
    pen.setWidth(30);
    painter->setPen(pen);
    painter->drawEllipse(_pos, _currentRadius,_currentRadius);

    pen.setColor(QColor(120,210,20));
    pen.setWidth(50);
    painter->setPen(pen);
    painter->setOpacity(0.75);
    painter->drawEllipse(_pos, _currentRadius-20,_currentRadius-20);

    painter->restore();
}
