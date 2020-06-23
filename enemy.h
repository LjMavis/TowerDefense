#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QString>
#include <QPoint>
#include "waypoint.h"
#include "playscene.h"

class PlayScene;  //与PlayScene相互包含头文件会报错。因此先要在这里声明一下，再在cpp中包含

class Enemy : public QObject//继承QObject才可使用槽函数
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, PlayScene *game,int Hp,qreal speed,int reward,QString path);

    void draw(QPainter *painter);//画出怪物
    void move();//移动

    PlayScene *	_game;//游戏界面


    QPixmap _pic;  //图像
    QPoint _pos;//位置坐标
    WayPoint* _destinationWayPoint;//目标路径点
    bool _active;//敌人是否被激活
    int _maxHp;//初始血量
    int _currentHp;//当下血量
    qreal _walkingSpeed;//移动速度
    int _reward;//击败后获得的金币
signals:

public slots:
    void doActivate();  //激活敌人，使之出现
};

#endif // ENEMY_H
