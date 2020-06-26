#ifndef INTRO_H
#define INTRO_H

#include <QMainWindow>

class Intro : public QMainWindow
{
    Q_OBJECT
public:
    explicit Intro(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号,返回主界面,不需要实现
    void chooseBack();

public slots:
};

#endif // INTRO_H
