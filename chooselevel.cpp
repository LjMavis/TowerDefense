#include "chooselevel.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mybutton.h"
#include "playscene.h"
ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡的界面
    this->setFixedSize(780,520);
    this->setWindowTitle("Choose Level");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu =bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //配置背景音乐
    bgm2player.setMedia(QUrl("qrc:/res/music/bgm2.mp3"));
    bgm2player.setVolume(15);
//    bgm2player.play();

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
            emit this->chooseSceneBack();//发出信号，让主界面监听

        });
        bgm2player.stop();//返回主界面就停止播放背景音乐
    });

    //选择关卡的按钮
    //水平排列4个关卡的选择
    for(int i=0;i<3;i++){
        MyButton * levelBtn = new MyButton(":/res/bt.png");
        levelBtn->setParent(this);
        levelBtn->move((i+1)*this->width()/4-levelBtn->width(),this->height()*0.25);

        //监听关卡选择
        connect(levelBtn,&MyButton::clicked,[=](){
            QString str = QString("选择第%1关").arg(i+1);
            qDebug()<<str;
            levelBtn->zoom1();//做弹起特效
            levelBtn->zoom2();
            play = new PlayScene(i+1);
            QTimer::singleShot(400,this,[=](){
                //进入游戏场景
                this->hide();//隐藏关卡选择界面
                bgm2player.stop();//停止播放背景音乐
                play->show();//显示游戏界面
                play->bgm3player.play();//播放游戏界面音乐
            });
            //监听游戏界面的返回按钮
            connect(play,&PlayScene::playSceneBack,this,[=](){
                this->show();//重新显示关卡选择界面
                delete play;//关闭上一游戏界面
                play=NULL;
                bgm2player.play();//继续播放背景音乐
            });
        });

        //在按钮上显示数字
        QLabel * label =new QLabel;
        label->setParent(this);
        label->setFixedSize(levelBtn->width(),levelBtn->height());//设置大小
        label->setText(QString::number(i+1));
        label->move((i+1)*this->width()/4-levelBtn->width(),this->height()*0.25);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置水平、垂直居中
        QFont ft;//设置字体大小
        ft.setPointSize(16);
        label->setFont(ft);
        QPalette pa;//设置字体颜色
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);

        //让鼠标穿透label 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }//关卡选择按钮设置结束

}
void ChooseLevel::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);//创建画家，指定绘图设备
    QPixmap pix;//创建QPixmap对象
    pix.load(":/res/levelscene.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//绘制背景

    //加载标题
    //pix.load(":/res/pla")//加载图片
    //pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//对pix缩放
    //painter.drawPixmap(10,30,pix);//绘制pix
}
