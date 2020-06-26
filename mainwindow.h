#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevel.h"
#include <QMediaPlayer>
#include "intro.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //重写paintEvent事件，画主场景背景
    void paintEvent(QPaintEvent *);

    //关卡选择界面
    ChooseLevel * chooseScence = NULL;

    //游戏简介界面
    Intro * introScence = NULL;

private:
    Ui::MainWindow *ui;

    QMediaPlayer bgm1player;//主菜单背景音乐
};

#endif // MAINWINDOW_H
