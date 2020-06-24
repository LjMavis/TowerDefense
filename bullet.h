#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPainter>
class PlayScene;
class Enemy;

class Bullet : public QObject
{
    Q_OBJECT
    //属性系统（The Property System），将m_currentPos注册为属性(property)，可用动画（QPropertyAnimation）类及其功能
    //用READ函数读取变量，用WRITE函数修改变量
    Q_PROPERTY(QPoint _currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,PlayScene *game);
    //起点、终点、伤害、指针目标敌人、指针
    QPoint currentPos() { return _currentPos; }              //返回当前坐标
    void setCurrentPos( QPoint pos ) { _currentPos = pos; }  //修改现在坐标
    void move();                                              //移动动画，QPropertyAnimation在其中
    void draw( QPainter *painter );                           //绘制子弹
    void setPix(QString path){_pic.load(path);}            //修改图片

    Enemy *	getTargetEnemy(){return	_targetEnemy;}//返回攻击的目标敌人
    PlayScene *	getGame(){return   _game;}//返回作用窗口
    int	getDamage(){return		_damage;}//伤害值


private slots:
    void hitTarget();//击中敌人

private:
    const QPoint	_startPos;//起始坐标
    const QPoint	_targetPos;//终点坐标
    QPoint			_currentPos;//当前坐标
    QPixmap	        _pic;//子弹的图片
    Enemy *			_targetEnemy;//攻击的目标敌人
    PlayScene *	    _game;//作用窗口
    int				_damage;//伤害值

//    static const QSize ms_fixedSize;//固定子弹大小
};

#endif // BULLET_H
