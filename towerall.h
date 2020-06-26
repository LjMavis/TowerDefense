#ifndef TOWERALL_H
#define TOWERALL_H

#include <QObject>
#include <QMediaPlayer>
#include "towerparent.h"
class TowerAll : public TowerParent
{
    Q_OBJECT
public:
    explicit TowerAll(QPoint pos, QString path, PlayScene *game);
    void levelUp();
    QMediaPlayer allPlayer;//群攻音效
signals:

public slots:
    void shootWeapon();
};

#endif // TOWERALL_H
