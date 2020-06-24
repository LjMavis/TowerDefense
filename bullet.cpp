#include "bullet.h"
#include "enemy.h"
#include "playscene.h"

#include <QAnimationDriver>
#include <QPropertyAnimation>
#include <QList>

Bullet::Bullet(QPoint startPos, QPoint targetPos, int damage, Enemy *target,PlayScene *game):
    _startPos(startPos+QPoint(25,25))
  , _targetPos(targetPos)
  , _currentPos(startPos)
  //,_pic(QPixmap(":/res/bullet1.png"))
  , _targetEnemy(target)
  , _game(game)
  , _damage(damage)
  {
    setPix(":/res/bullet1.png");
}

void Bullet::draw(QPainter *painter)
{
    painter->drawPixmap(_currentPos.x(),_currentPos.y(),14,14,_pic);//在当前位置画出子弹
}

void Bullet::move()  //子弹移动
{
    static const int duration = 100;  //存放动画持续时间（在100毫秒内击中敌人）

    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentPos");
    animation->setDuration(duration);      //设置持续时间
    animation->setStartValue(_startPos);  //设置起点坐标
    animation->setEndValue(_targetPos);   //设置终点坐标

    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
        //关联animation->finished()与Bullet的hitTarget()：动画结束,触发 击中敌人

    animation->start();  //动画开始
        //animation->start()后，动画自动进行，不用再管，无须每帧设置中途各点坐标
}

void Bullet::hitTarget()//击中目标
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (_game->enemyList().indexOf(_targetEnemy) != -1)
        _targetEnemy->getDamage(_damage);//目标受到伤害
    _game->removedBullet(this);
}
