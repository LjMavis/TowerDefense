#include "towerparent.h"
#include <QString>
#include <QPainter>
#include <QDebug>
TowerParent::TowerParent(QPoint pos,QString path)
{
//    m_level = 0;
    _pos = pos;
    _range=200;
    _damage=5;
    _cd= 1500;
    TowerPath = path;
    _w=45;
    _h=45;
//    m_targetEnemy = NULL;
//    m_game = game;
//    m_game2 = NULL;
//    m_fireRateTimer = new QTimer(this);
//    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
//    m_player.setMedia(QUrl("qrc:/pic/music/towersound.mp3"));
//    m_player.setVolume(30);
}
QPoint TowerParent::getPos(){
    return this->_pos;
}
void TowerParent::draw(QPainter *painter){
//    painter->save();
    painter->setPen(Qt::white);// 绘制攻击范围
    painter->drawEllipse(_pos.x()+25-_range/2,_pos.y()+25-_range/2,_range,_range);
    // 尺寸大小派上用场了,当然也可以直接获取图片大小,是一样的
//    static const QPoint offsetPoint(-40,-40);
    // 绘制炮塔并选择炮塔
    // 这里将坐标原点移到m_pos,绘制的适合,就要加上那个偏移点到左上角
//    painter->translate(_pos);
    QPixmap pix;
    bool ret=(pix.load(TowerPath));
    if(!ret){
        qDebug()<<"加载图片出错";
    }
    painter->drawPixmap(_pos.x()+25-_w/2,_pos.y()+25-_h/2,_w,_h,pix);
//    painter->restore();
}
