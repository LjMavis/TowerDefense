#ifndef TOWERALL_H
#define TOWERALL_H

#include <QObject>
#include "towerparent.h"
class TowerAll : public TowerParent
{
    Q_OBJECT
public:
    explicit TowerAll(QPoint pos, QString path, PlayScene *game);

signals:

public slots:
    void shootWeapon();
};

#endif // TOWERALL_H
