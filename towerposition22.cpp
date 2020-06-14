#include "towerposition22.h"
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QAction>

TowerPosition22::TowerPosition(QPoint pos){
    this->pos =pos;
    //给塔坑创建菜单，右键出现
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction * action= new QAction(this);
    action->setText("hello");
    this->addAction(action);
}

//int TowerPosition22::GetX() const     //获取横坐标
//{
//    return _x;
//}

//int TowerPosition22::GetY() const     //获取横坐标
//{
//    return _y;
//}

//int TowerPosition::GetWidth() const //获取宽
//{
//    return mwidth;
//}

//int TowerPosition::GetHeight() const //获取高
//{
//    return mheight;
//}
