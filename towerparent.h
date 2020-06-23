#ifndef TOWERPARENT_H
#define TOWERPARENT_H

#include <QPixmap>
#include <QPoint>
#include <QPainter>
class TowerParent
{
public:
    TowerParent(QPoint pos,QString path);
    QPoint getPos();//获取图片路径
    void draw(QPainter *painter);
private:
    QPoint _pos;//塔的位置，左上角坐标
    int _w,_h;//图片的宽、高
    int _range;//塔的射程
    int _damage;//塔的攻击力
    int _cd;//攻击间隔时间
    QString TowerPath;//塔的图片的路径
};

#endif // TOWERPARENT_H
