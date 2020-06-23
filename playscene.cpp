#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QList>
#include "mybutton.h"
#include "towerposition.h"
#include "towerparent.h"
#include "towerpapyrus.h"

PlayScene::PlayScene(int level)
{
    //设置计时器
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));  //关联时间与updateMap()函数
    timer->start(20);  //每多少毫秒传递一次时间信号 //帧数

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));

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

    //加载塔坑
    loadTowerPosition();

    //加载路线
    loadWayPoint();

    //绘制防御塔
    PaintTower();

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

    //设置初始金币数、生命值、已有攻击波数
    this->gold=400;
    this->life=10;
    this->wave=0;

//    //显示金币数
//    QLabel * goldLb = new QLabel;
//    goldLb->setParent(this);
//    this->gold=400;
//    QString gold = QString("Gold: %1").arg(this->gold);
//    goldLb->setFont(font);
//    goldLb->setText(gold);
//    goldLb->setGeometry(20,470,150,50);

//    //显示生命值
//    QLabel * lifeLb = new QLabel;
//    lifeLb->setParent(this);
//    this->life=10;
//    QString life = QString("Life: %1").arg(this->life);
//    lifeLb->setFont(font);
//    lifeLb->setText(life);
//    lifeLb->setGeometry(170,470,100,50);


}

void PlayScene::loadTowerPosition(){
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
    //第二关的塔坑
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
    if(levelIndex==1)//布置第一关的塔坑
    {
        len	= sizeof(map1) / sizeof(map1[0]);
        for (int i = 0; i < len; ++i){
            TowerPosition *tp=new TowerPosition(map1[i]);
            tp->setParent(this);//设置父类
            tp->move(map1[i]);
//            connect(tp,&TowerPosition::chooseSans,this,[=](){
//                qDebug()<<"选择了Sans";
//            });
            towerPositions_list.push_back(tp);
        }


    }
    else if(levelIndex==2)//布置第二关的塔坑
    {
        len	= sizeof(map2) / sizeof(map2[0]);
        for (int i = 0; i < len; ++i){
            TowerPosition *tp=new TowerPosition(map2[i]);
            tp->setParent(this);//设置父类
            tp->move(map2[i]);
//            QPixmap pix;//创建QPixmap对象
//            pix.load(":/res/pot.jpg");//加载图片
//            painter.drawPixmap(map2[i].x(),map2[i].y(),50,50,pix);//绘制塔坑
            towerPositions_list.push_back(tp);
        }
    }

}
void PlayScene::loadWayPoint()//添加路线
{
    if(levelIndex==1){
        WayPoint *wayPoint1 = new WayPoint(QPoint(695, 170));
        wayPoints_list.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(695, 230));
        wayPoints_list.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(625, 230));
        wayPoints_list.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(625, 390));
        wayPoints_list.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(400, 390));
        wayPoints_list.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(400, 130));
        wayPoints_list.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(175, 130));
        wayPoints_list.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(175, 290));
        wayPoints_list.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(0, 290));
        wayPoints_list.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);
    }
    else if(levelIndex==2){
        WayPoint *wayPoint1 = new WayPoint(QPoint(695, 145));
        wayPoints_list.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(695, 195));
        wayPoints_list.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(550, 195));
        wayPoints_list.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(550, 95));
        wayPoints_list.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(385, 95));
        wayPoints_list.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(385, 180));
        wayPoints_list.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(135, 180));
        wayPoints_list.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(135, 295));
        wayPoints_list.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(385, 295));
        wayPoints_list.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);

        WayPoint *wayPoint10 = new WayPoint(QPoint(385, 405));
        wayPoints_list.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);

        WayPoint *wayPoint11 = new WayPoint(QPoint(0, 405));
        wayPoints_list.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);

    }
}
void PlayScene::PaintTower()//画出防御塔
{
    auto p=towerPositions_list.begin();
    while(p!=towerPositions_list.end())//遍历所有塔坑
    {
        if(! (*p)->hasTower())//当此塔坑无塔时，放置防御塔
        {
            connect(*p,&TowerPosition::chooseSans,this,[=](){
                qDebug()<<"选择了Sans";
                if(gold>=200){
                    gold-=200;
                    (*p)->setTower();//设置为有塔
                    TowerParent *tower=new TowerParent((*p)->pos,":/res/sans.png");//创建一个塔
                    tower_list.push_back(tower);
                    qDebug()<<"放置Sans";
                    (*p)->hide();
                    update();
                }
            });
            connect(*p,&TowerPosition::choosePapyrus,this,[=](){
                qDebug()<<"选择了Papyrus";
                if(gold>=200){
                    gold-=200;
                    (*p)->setTower();//设置为有塔
                    TowerPapyrus *tower=new TowerPapyrus((*p)->pos,":/res/pap.png");//创建一个塔
                    tower_list.push_back(tower);
                    qDebug()<<"放置Papyrus";
                    (*p)->hide();
                    update();
                }
            });
        }
//        break;
        p++;
    }
}
bool PlayScene::loadWave()
{
    if (wave >= 1+2*levelIndex)//每关攻击波数为1+关卡数*2
    {
        qDebug()<<"没有敌人了";
        return false;
    }
    qDebug()<<"开始加载敌人";
    int enemyStartInterval = 1500;  //敌人出现间隔
    WayPoint *startWayPoint = wayPoints_list.back(); // 这里是个逆序的，末项是起点
    for (int i = 0; i < wave*2+6; i++)//每一波出现的敌人
    {
        if(wave<2)//前两波，只有mtt1
        {
            Enemy *enemy = new Enemy(startWayPoint,this,40,1.0,100,":/res/mtt1.png");
            enemy_list.push_back(enemy);
            QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
                //singleShot相当于定时器，好处在于不需使用timer，在设置时间到后自动触发SLOT中的函数
        }
        else
        {
            //一样一个的插入
            if(i%2==0)//插入mtt1
            {
                Enemy *enemy = new Enemy(startWayPoint,this,40,1.0,100,":/res/mtt1.png");
                enemy_list.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
            }
            else//插入mtt2
            {
                Enemy *enemy = new Enemy(startWayPoint, this,80,2.0,150,":/res/mtt2.png");
                enemy_list.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
            }

        }
    }
    return true;
}
void PlayScene::gameStart()//开始游戏
{
    loadWave();
}

void PlayScene::updateMap()//刷新界面
{
    foreach (Enemy *enemy, enemy_list){
        enemy->move();
//        qDebug()<<"移动怪物";
    }
//	foreach (Tower *tower, m_towersList)
//		tower->checkEnemyInRange();
    update();
}
void PlayScene::drawGold(QPainter *painter)//显示金币数
{
    painter->setPen(QPen(Qt::black));
    QFont font=painter->font();
    font.setFamily("华文新魏");
    font.setPixelSize(24);
    painter->setFont(font);
    painter->drawText(QRect(20,490,150,100), QString("Gold: %1").arg(gold));
}
void PlayScene::drawLife(QPainter *painter)//显示玩家生命值
{
    painter->setPen(QPen(Qt::black));
    QFont font=painter->font();
    font.setFamily("华文新魏");
    font.setPixelSize(24);
    painter->setFont(font);
    painter->drawText(QRect(170,490,150,100), QString("Life: %1").arg(life));
}

void PlayScene::getLifeDamage(int damage)//玩家生命值-1
{
    life -= damage;
//    if (life <= 0)//判断游戏结束
//    {doGameOver();}
}

void PlayScene::removedEnemy(Enemy *enemy)//移除怪物
{
    enemy_list.removeOne(enemy);
    delete enemy;
    //如果屏幕上没有敌人
    if (enemy_list.empty())
    {
        ++this->wave; // 当前波数加1
        qDebug()<<"下一波";
        // 然后，继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，游戏胜利
            // 设置游戏胜利标志为true
//            m_gameWin = true;
            qDebug()<<"游戏胜利";
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(QString(":/res/map%1.jpg").arg(levelIndex));//背景待改
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景
    foreach(TowerParent * tower,tower_list) {tower->draw(&painter);}//绘制塔
    foreach (const WayPoint *wayPoint, wayPoints_list){wayPoint->draw(&painter);}//绘制路径
    foreach (Enemy *enemy, enemy_list) {enemy->draw(&painter); }//绘制怪物
    drawGold(&painter);//显示金币数
    drawLife(&painter);//显示玩家生命值
}
