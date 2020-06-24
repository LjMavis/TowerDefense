#ifndef TOWERFREEZE_H
#define TOWERFREEZE_H

#include <QObject>
#include "towerparent.h"

//具有减速效果
class TowerFreeze : public TowerParent
{
    Q_OBJECT
public:
    TowerFreeze(QPoint pos, QString path, PlayScene *game);
    qreal getSpeed(){return _speed;}

signals:

public slots:
    void shootWeapon();
private:
    qreal _speed;//减弱敌人速度
};

#endif // TOWERFREEZE_H
