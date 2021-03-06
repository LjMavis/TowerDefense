#include "towerposition1.h"
#include <QPushButton>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QAction>
#include <QDebug>
TowerPosition::TowerPosition(QPoint pos):pos(pos)/*,_hasTower(false)*/{
    QPixmap pix;
    bool ret=pix.load(":/res/pot.jpg");
    if(!ret){
        qDebug() << "按钮图片加载失败";
        return;
    }
    this->setFixedSize(50,50);//设置图片固定大小
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式
    this->setIcon(pix);//设置图标
    this->setIconSize(QSize(50,50));//设置图标大小
    //给塔坑创建菜单，右键出现
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction * action1= new QAction(this);
    action1->setText("Sans");
    this->addAction(action1);
    QAction * action2= new QAction(this);
    action2->setText("Papyrus");
    this->addAction(action2);
    QAction * action3= new QAction(this);
    action3->setText("Toriel");
    this->addAction(action3);
    QAction * action4= new QAction(this);
    action4->setText("Asgore");
    this->addAction(action4);
    //触发信号
    connect(action1,&QAction::triggered,this,[=](){
        emit chooseSans();//点击后触发信号
    });
}
//bool TowerPosition::hasTower() const{
//    return _hasTower;
//}
//int TowerPosition::GetX() const     //获取横坐标
//{
//    return _x;
//}

//int TowerPosition::GetY() const     //获取横坐标
//{
//    return _y;
//}
