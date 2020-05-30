#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include "towerposition.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);//构造，第i+1关

    int levelIndex;//记住所选的关卡


    //重写绘画事件
    void paintEvent(QPaintEvent *);

    //储存塔坑的位置
    void loadTowerPosition(QPainter &painter);

signals:
    //写一个自定义信号,返回关卡选择界面,不需要实现
    void playSceneBack();
private:
    QList<TowerPosition*> towerPositions_list;

public slots:
};

#endif // PLAYSCENE_H
