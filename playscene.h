#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include "towerposition.h"
#include "towerparent.h"
#include "waypoint.h"
#include "enemy.h"

class Enemy;

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);//构造，第i+1关

    int levelIndex;//记住所选的关卡
    int gold;//金币数
    int life;//生命值
    int wave;//怪物波数


    //重写绘画事件
    void paintEvent(QPaintEvent *);

    //画出塔坑
    void loadTowerPosition();

    //添加路线
    void loadWayPoint();

    //画出防御塔
    void PaintTower();

    //加载攻击波数
    bool loadWave();

    void drawGold(QPainter *painter);//显示金币数
    void drawLife(QPainter *painter);//显示玩家生命值

    //玩家生命值减少
    void getLifeDamage(int damage = 1);

    //移除不用的敌人
    void removedEnemy(Enemy *enemy);

signals:
    //写一个自定义信号,返回关卡选择界面,不需要实现
    void playSceneBack();
private:
    QList<TowerPosition *> towerPositions_list;//存塔坑
    QList<TowerParent *> tower_list;//存塔
    QList<WayPoint *> wayPoints_list;//存路径点
    QList<Enemy *> enemy_list;//存怪物
public slots:
    void updateMap();  //定时刷新界面
    void gameStart();//游戏开始
};

#endif // PLAYSCENE_H
