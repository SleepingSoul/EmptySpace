#ifndef HEAVYENEMY_H
#define HEAVYENEMY_H

#include "enemy.h"

class HeavyEnemy : public Enemy
{
public:
    HeavyEnemy();
    ~HeavyEnemy();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private slots:
    void slotShoot() override;
    void slotTimer() override;
};

#endif // HEAVYENEMY_H
