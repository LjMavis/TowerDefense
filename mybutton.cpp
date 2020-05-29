#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyButton::MyButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgpath=pressImg;
    QPixmap pix;
    bool ret=pix.load(normalImg);//判断是否能正常加载
    if(!ret){
        qDebug() << "按钮图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());//设置图片固定大小
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式
    this->setIcon(pix);//设置图标
    this->setIconSize(QSize(pix.width(),pix.height()));//设置图标大小
}
void MyButton::zoom1(){
    //创建动画特效
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);//设置动画时间间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));//起始位置
    animation->setEndValue(QRect(this->x(),this->y()+8,this->width(),this->height()));//结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);//弹跳曲线
    animation->start();//执行特效
}
void MyButton::zoom2(){
    //创建动画特效
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);//设置动画时间间隔
    animation->setStartValue(QRect(this->x(),this->y()+8,this->width(),this->height()));//起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));//结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);//弹跳曲线
    animation->start();//执行特效
}

//void MyButton::mousePressEvent(QMouseEvent *e){
////    //传入的图片不为空
////    if(this->pressImgpath != ""){

////    }
//}
//void MyButton::mouseReleaseEvent(QMouseEvent *e){

//}
