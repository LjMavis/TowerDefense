#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPushButton>
#include <QPoint>
#include <QPixmap>
#include <QAction>
class TowerParent;
class TowerPosition : public QPushButton
{
    Q_OBJECT
public:
    TowerPosition(QPoint pos);//设置塔坑

    TowerParent *getTower(){return _tower;}

    QPoint pos;//塔坑位置

    bool containPoint(const QPoint &pos) const;//判断鼠标是否点击在塔坑里

    bool hasTower();//是否有塔

    void setTower(TowerParent *tower);//设置为有塔
    void setNoTower(){_hasTower=false;}//设置为无塔

    bool _hasTower = false;
    TowerParent * _tower;
signals:
    void chooseSans();
    void choosePapyrus();
    void chooseAsgore();
public slots:
};

#endif // TOWERPOSITION_H
