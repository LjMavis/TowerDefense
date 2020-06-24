#ifndef TOWERPARENT_H
#define TOWERPARENT_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include "enemy.h"
class PlayScene;
class Enemy;
class Bullet;
class TowerParent : public QObject
{
    Q_OBJECT
public:
    TowerParent(QPoint pos, QString path, PlayScene *game);
    ~TowerParent();
    QPoint getPos();//获取图片路径
    void draw(QPainter *painter);//绘制塔
    void attackEnemy(Enemy *enemy);//启动攻击
    void targetKilled();//目标死亡，重置攻击对象为NULL
    void loseEnemy();//目标离开攻击范围，重置攻击对象为NULL

    void setDamage(int a,int b,int c){_damage[0]=a;_damage[1]=b;_damage[2]=c;}
    void setCd(int a,int b,int c){_cd[0]=a;_cd[1]=b;_cd[2]=c;}

    Enemy * getTargetEnemy(){return _targetEnemy;}
    PlayScene * getGame(){return _game;}
    int getAttackRange(){return _range[_level];}
    int getDamage(){return _damage[_level];}

    void attack();

//    void checkEnemyInRange();

    /*virtual */void levelUp();

private:
    QPoint _pos;//塔的位置，左上角坐标
    int _level;//用于进行升级
    int _w,_h;//图片的宽、高
    int _range[3];//塔的射程
    int _damage[3];//塔的攻击力
    int _cd[3];//攻击间隔时间
    QString TowerPath;//塔的图片的路径
    QTimer *_fireRateTimer;//发射子弹的计时器
    Enemy *_targetEnemy;//攻击对象
    PlayScene * _game;

signals:

public slots:
    virtual void shootWeapon();//发射子弹
};

#endif // TOWERPARENT_H
