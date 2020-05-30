#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QList>
#include "mybutton.h"
#include "towerposition.h"

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

void PlayScene::loadTowerPosition(QPainter& painter){
    //第一关的塔坑
    QPoint map1[]=
    {
        QPoint(80,200),
        QPoint(220,173),
        QPoint(310,173),
        QPoint(430,305),
        QPoint(530,305),
        QPoint(660,280)
    };
    QPoint map2[]=
    {
        QPoint(130,320),
        QPoint(300,320),
        QPoint(170,210),
        QPoint(355,210),
        QPoint(295,95),
        QPoint(440,130),
        QPoint(595,110)
    };
    int len;
    if(levelIndex==1){
        len	= sizeof(map1) / sizeof(map1[0]);
        for (int i = 0; i < len; ++i){
            TowerPosition *tp=new TowerPosition(map1[i]);
            QPixmap pix;//创建QPixmap对象
            pix.load(":/res/pot.jpg");//加载图片
            painter.drawPixmap(map1[i].x(),map1[i].y(),50,50,pix);//绘制背景
            towerPositions_list.push_back(tp);
        }
    }
    else if(levelIndex==2){
        len	= sizeof(map2) / sizeof(map2[0]);
        for (int i = 0; i < len; ++i){
            TowerPosition *tp=new TowerPosition(map2[i]);
            QPixmap pix;//创建QPixmap对象
            pix.load(":/res/pot.jpg");//加载图片
            painter.drawPixmap(map2[i].x(),map2[i].y(),50,50,pix);//绘制背景
            towerPositions_list.push_back(tp);
        }
    }
//    switch (levelIndex)
//    {
//    case 1:
//        len	= sizeof(map1) / sizeof(map1[0]);
//        for (int i = 0; i < len; ++i){
//            TowerPosition *tp=new TowerPosition(map1[i]);
//            QPixmap pix;//创建QPixmap对象
//            pix.load(":/res/pot.jpg");//加载图片
//            painter.drawPixmap(map1[i].x(),map1[i].y(),50,50,pix);//绘制背景
//            towerPositions_list.push_back(tp);
//        }
//        break;
//    case 2:
//        len	= sizeof(map2) / sizeof(map1[0]);
//        for (int i = 0; i < len; ++i){
//            TowerPosition *tp=new TowerPosition(map2[i]);
//            QPixmap pix;//创建QPixmap对象
//            pix.load(":/res/pot.jpg");//加载图片
//            painter.drawPixmap(map2[i].x(),map1[i].y(),50,50,pix);//绘制背景
//            towerPositions_list.push_back(tp);
//        }
//        break;
//    case 3:
//        memcpy(Map, Map_3, sizeof(Map));
//        break;
//    case 4:
//        memcpy(Map, Map_3, sizeof(Map));
//        break;
//    default:
//        break;
//    }

}


void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(QString(":/res/map%1.jpg").arg(levelIndex));//背景待改
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景
    loadTowerPosition(painter);
}
