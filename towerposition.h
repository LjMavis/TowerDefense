#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

//塔坑类
class TowerPosition : public QObject
{
    Q_OBJECT
public:
    TowerPosition(QPoint pos);//设置塔坑

    QPoint pos;//塔坑位置



signals:

public slots:
};

#endif // TOWERPOSITION_H
