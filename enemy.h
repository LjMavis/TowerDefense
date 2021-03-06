#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QTimer>
//#include <QCoreApplication>//为了解决 no such slot
#include "waypoint.h"


class TowerParent;
class PlayScene;  //与PlayScene相互包含头文件会报错。因此先要在这里声明一下，再在cpp中包含
class Enemy : public QObject
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);
    Enemy(WayPoint *startWayPoint, PlayScene *game,int Hp,double speed,int reward,QString path,bool ifstrong);

//    void recoverSpeed();//恢复原本的速度
//    void judgeLife();//判断是否还活着
//    bool judgeLife();
    void draw(QPainter *painter);//画出怪物
    void move();//移动
    void getAttacked(TowerParent *tower );  //列入该tower攻击列表
    void getDamage(int damage);     //受到Bullet伤害
    void getRemoved();               //怪物死亡，被移除
    QPoint getPos(){return _pos;}//获取坐标
    bool ifAlive();//判断是否还活着
    bool ifFreezed(){return _freezed;}//获取是否被减速
    bool ifAll(){return _alled;}//获取是否被群攻扫描
    void getFreezed();//受到ice伤害，被减速
    void setAlled();//设置为被群攻扫描到
    bool getStrong(){return _strong;}//获取是否无视减速
//    QTimer *_timer=new QTimer();

    PlayScene *	_game;//游戏界面

    QList<TowerParent *> _attackedTowerList;//所有攻击来源的tower的列表，用来enemy消失时反馈
    QPixmap _pic;  //图像
    QPoint _pos;//位置坐标
    WayPoint* _destinationWayPoint;//目标路径点
    bool _active;//敌人是否被激活
//    bool _freezed;//敌人是否被减速
//    bool _alled;//敌人是否被群攻
    int _maxHp;//初始血量
    int _currentHp;//当下血量
//    double _walkingSpeed;//移动速度
//    double _currentSpeed;//当下速度
    int _reward;//击败后获得的金币
private:
    double _walkingSpeed;//移动速度
    double _currentSpeed;//当下速度
    bool _freezed;//敌人是否被减速
    bool _alled;//敌人是否被群攻
    bool _strong;//敌人是否可以无视减速

signals:

public slots:
    void doActivate();  //激活敌人，使之出现
    void recoverSpeed();//恢复原本的速度
    void recover();
//    void judgeLife();//判断是否还活着
private slots:
//    void judgeLife();//判断是否还活着
//    void recoverSpeed();//恢复原本的速度
//    void recover();
};

#endif // ENEMY_H
