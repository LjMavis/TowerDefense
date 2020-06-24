#ifndef ALL_H
#define ALL_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
class PlayScene;

//群攻的光波
class All : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int _currentRadius
               READ currentRadius
               WRITE setCurrentRadius)
public:
    All(QPoint position, int targetRadius, int damage, PlayScene *game);//构造

    int currentRadius() { return _currentRadius; }//获取当前半径
    void setCurrentRadius( int radius ) { _currentRadius = radius; }//设置当前半径
    void move();//光波移动
    void draw( QPainter *painter );//画出光波

    QPoint getPos(){return _pos;}//获取坐标
    int getTargetRadius(){return _targetRadius;}//获取攻击半径
    int getDamage(){return _damage;}//获取攻击伤害

public slots:

    void hitTarget();

private:
    PlayScene *_game;
    int _damage;//伤害
    QPoint _pos;//坐标（塔的）
    int _targetRadius;//攻击范围半径
    int _currentRadius;//当下光波半径
};

#endif // ALL_H
