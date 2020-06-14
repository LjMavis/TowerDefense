#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPushButton>
#include <QPoint>
#include <QPixmap>
#include <QAction>

//塔坑类
class TowerPosition22 : public QPushButton
{
    Q_OBJECT
public:
    TowerPosition(QPoint pos);//设置塔坑

    QPoint pos;//塔坑位置

    int GetX() const;     //获取横坐标
    int GetY() const;     //获取横坐标
//    int GetWidth() const; //获取宽
//    int GetHeight() const;//获取高


signals:

public slots:
private:
    const int _x, _y;           //位置坐标
    const int _width=50, _height=50;  //宽高


};

#endif // TOWERPOSITION_H
