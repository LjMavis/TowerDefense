#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QMediaPlayer>
#include "mybutton.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置主界面
    setFixedSize(780,520);//设置窗口固定大小
    //setWindowIcon(QIcon(":/res/Coin0001.png")); //设置图标
    setWindowTitle("MainScene");//设置标题

    //实现菜单退出
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //配置背景音乐
    bgm1player.setMedia(QUrl("qrc:/res/music/bgm1.mp3"));
    bgm1player.setVolume(15);
    bgm1player.play();

    //游戏开始按钮
    MyButton * start = new MyButton(":/res/start.png");
    start->setParent(this);
    start->move(this->width()*0.5-start->width()*0.5,300);

    //游戏介绍按钮
    MyButton * intro = new MyButton(":/res/introBtn.png");
    intro->setParent(this);
    intro->move(this->width()*0.5-start->width()*0.5,350);

    chooseScence = new ChooseLevel;//创建关卡选择界面
    introScence = new Intro;//游戏简介界面

    //监听关卡选择界面的返回按钮
    connect(chooseScence,&ChooseLevel::chooseSceneBack,this,[=](){
        chooseScence->hide();//隐藏关卡选择界面
        this->show();//重新显示主界面
        bgm1player.play();//重新播放背景音乐
    });
    //监听游戏简介界面的返回按钮
    connect(introScence,&Intro::chooseBack,this,[=](){
        introScence->hide();//隐藏游戏简介界面
        this->show();//重新显示主界面
    });

    connect(start,&MyButton::clicked,[=](){
        qDebug()<<"点击游戏开始";
        start->zoom1();//做弹起特效
        start->zoom2();
        //延时0.4秒
        QTimer::singleShot(400,this,[=](){
            this->hide();//隐藏主界面
            chooseScence->show();//进入关卡选择界面
        });
        bgm1player.stop();//点击游戏开始，就停止播放背景音乐
        chooseScence->bgm2player.play();
    });

    connect(intro,&MyButton::clicked,[=](){
        qDebug()<<"点击游戏介绍";
        intro->zoom1();//做弹起特效
        intro->zoom2();
        //延时0.4秒
        QTimer::singleShot(400,this,[=](){
            this->hide();//隐藏主界面
            introScence->show();//进入游戏简介界面
        });
    });

}
//设置主界面背景图片
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);//创建画家，指定绘图设备
    QPixmap pix;//创建QPixmap对象
    pix.load(":/res/pic.jpg");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景

    //加载标题
    //pix.load(":/res/pla")//加载图片
    //pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//对pix缩放
    //painter.drawPixmap(10,30,pix);//绘制pix

}

MainWindow::~MainWindow()
{
    delete ui;
}
