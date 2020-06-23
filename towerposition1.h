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
//    bool hasTower() const;//是否有塔
//    int GetX() const;     //获取横坐标
//    int GetY() const;     //获取横坐标
//private:
//    bool _hasTower;
signals:
    void chooseSans() const;//按钮菜单选择了Sans的信号
public slots:
};

#endif // TOWERPOSITION1_H
