#include "towerposition.h"
#include <QPushButton>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QAction>
#include <QDebug>
#include "towerparent.h"
TowerPosition::TowerPosition(QPoint pos):pos(pos){
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
    action1->setText("Sans 200");
    this->addAction(action1);
    QAction * action2= new QAction(this);
    action2->setText("Papyrus 250");
    this->addAction(action2);
//    QAction * action3= new QAction(this);
//    action3->setText("Toriel");
//    this->addAction(action3);
    QAction * action3= new QAction(this);
    action3->setText("Asgore 300");
    this->addAction(action3);
    //触发信号
    connect(action1,&QAction::triggered,this,[=](){
        emit chooseSans();//点击后触发信号
    });
    connect(action2,&QAction::triggered,this,[=](){
        emit choosePapyrus();//点击后触发信号
    });
    connect(action3,&QAction::triggered,this,[=](){
        emit chooseAsgore();//点击后触发信号
    });
}

bool TowerPosition::hasTower(){
    return _hasTower;
}
void TowerPosition::setTower(TowerParent * tower){
    _hasTower=true;
    _tower=tower;
}
//用于鼠标点击事件
bool TowerPosition::containPoint(const QPoint &pos) const
{
    bool isXInHere = this->pos.x() < pos.x() && pos.x() < (this->pos.x()+50);
    bool isYInHere = this->pos.y() < pos.y() && pos.y() < (this->pos.y()+50);
    return isXInHere && isYInHere;
}
