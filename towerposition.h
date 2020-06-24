#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

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

    bool hasTower();//是否有塔

    void setTower();//设置为有塔

    bool _hasTower = false;
signals:
    void chooseSans();
    void choosePapyrus();
    void chooseAsgore();
public slots:
};

#endif // TOWERPOSITION_H
