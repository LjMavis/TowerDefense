#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mybutton.h"
#include "intro.h"

Intro::Intro(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡的界面
    this->setFixedSize(780,520);
    this->setWindowTitle("Game Introduction");

    //返回按钮
    MyButton * back = new MyButton(":/res/back.png");
    back->setParent(this);
    back->move(this->width()-back->width(),this->height()-back->height());

    //实现返回主界面
    connect(back,&MyButton::clicked,[=](){
        qDebug()<<"点击返回主菜单";
        back->zoom1();//做弹起特效
        back->zoom2();
        //延时0.4秒
        QTimer::singleShot(400,this,[=](){
            emit this->chooseBack();//发出信号，让主界面监听

        });
    });
}

void Intro::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);//创建画家，指定绘图设备
    QPixmap pix;//创建QPixmap对象
    pix.load(":/res/intro.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景
}
