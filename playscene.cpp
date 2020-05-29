#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "mybutton.h"
PlayScene::PlayScene(int level)
{
    QString str = QString("进入第%1关").arg(level);
    qDebug()<<str;
    this->levelIndex=level;

    //初始化游戏场景
    this->setFixedSize(780,520);
    this->setWindowTitle("paly scene");

    //创建菜单栏的退出按钮
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu =bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyButton * back = new MyButton(":/res/back.png");
    back->setParent(this);
    back->move(this->width()-back->width(),this->height()-back->height());

    //实现返回关卡选择界面
    connect(back,&MyButton::clicked,[=](){
        qDebug()<<"点击返回选择关卡界面";
        back->zoom1();//做弹起特效
        back->zoom2();
        //延时0.3秒
        QTimer::singleShot(300,this,[=](){
            emit this->playSceneBack();//发出信号，让选择关卡界面监听
        });
    });

    //显示当前关卡数
    QLabel * levelLb = new QLabel;
    levelLb->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString lev = QString("Level: %1").arg(this->levelIndex);
    levelLb->setFont(font);
    levelLb->setText(lev);
    levelLb->setGeometry(20,20,100,50);
}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(QString(":/res/map%1.jpg").arg(levelIndex));//背景待改
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景
}
