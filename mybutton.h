#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyButton(QWidget *parent = nullptr);

    MyButton(QString normalImg, QString pressImg = "");//构造函数 正常显示图片路径，按下后图片路径
    //保存正常及按下后显示图片的路径
    QString normalImgPath;
    QString pressImgpath;

    //弹跳特效
    void zoom1();//向下弹跳
    void zoom2();//向上弹跳

//    //按钮的按下和释放事件
//    void mousePressEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYBUTTON_H
