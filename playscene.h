#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include <QMediaPlayer>
#include "towerposition.h"
#include "towerparent.h"
#include "waypoint.h"
#include "enemy.h"
class TowerParent;
class Enemy;
class Bullet;
class Ice;
class All;
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);//构造，第i+1关

    int levelIndex;//记住所选的关卡
    int gold;//金币数
    int life;//生命值
    int wave;//怪物波数

    QMediaPlayer bgm3player;//游戏背景音乐
    QMediaPlayer setTowerPlayer;//放置和拆除塔的音效
    QMediaPlayer levelUpPlayer;//塔进行升级的音效
    QMediaPlayer winPlayer;//游戏胜利的音效
    QMediaPlayer losePlayer;//游戏失败的音效

    QList<Enemy *> enemyList() const;//获取enemy_list

    //重写绘画事件
    void paintEvent(QPaintEvent *);

    //鼠标点击事件，升级+移除
    void mousePressEvent(QMouseEvent *);

    //画出塔坑
    void loadTowerPosition();

    //添加路线
    void loadWayPoint();

    //画出防御塔
    void PaintTower();

    //加载攻击波数
    bool loadWave();

    //加入子弹
    void addBullet(Bullet *bullet);
    void addIce(Ice *ice);//加入减速子弹
    void addAll(All *all);//加入群攻光波

    void drawGold(QPainter *painter);//显示金币数
    void drawLife(QPainter *painter);//显示玩家生命值
    void drawWave(QPainter *painter);//显示当前攻击波数

    //群攻光波击中效果
    void allEffect(All *all);

    //

    //玩家获得金币
    void awardGold(int gold);

    //玩家生命值减少
    void getLifeDamage(int damage = 1);

    //移除不用的敌人
    void removedEnemy(Enemy *enemy);

    //移除子弹
    void removedBullet(Bullet *bullet);
    void removedIce(Ice *ice);
    void removedAll(All *all);



signals:
    //写一个自定义信号,返回关卡选择界面,不需要实现
    void playSceneBack();
private:
    bool _gameWin=false,_gameLose=false;

    QList<TowerPosition *> towerPositions_list;//存塔坑
    QList<TowerParent *> tower_list;//存塔
    QList<WayPoint *> wayPoints_list;//存路径点
    QList<Enemy *> enemy_list;//存怪物
    QList<Bullet *>bullet_list;//存子弹
    QList<Ice *>ice_list;//存减速子弹
    QList<All *>all_list;//存群攻光波
public slots:
    void updateMap();  //定时刷新界面
    void gameStart();//游戏开始
};

#endif // PLAYSCENE_H
