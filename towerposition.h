#ifndef TOWERPOSITION1_H
#define TOWERPOSITION1_H

#include <QPushButton>
#include <QPoint>
#include <QPixmap>
#include <QAction>

class TowerPosition : public QPushButton
{
    Q_OBJECT
public:
    TowerPosition(QPoint pos);//设置塔坑

    QPoint pos;//塔坑位置

//    int GetX() const;     //获取横坐标
//    int GetY() const;     //获取横坐标
signals:

public slots:
};

#endif // TOWERPOSITION1_H
