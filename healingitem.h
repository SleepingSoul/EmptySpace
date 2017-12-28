#ifndef HEALINGITEM_H
#define HEALINGITEM_H

#include "gameplayitem.h"

class HealingItem : public GameplayItem
{
public: 
    HealingItem();
    ~HealingItem();

    void stopTime() override {}
    void startTime() override {}

    int type() const override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    QPixmap *pic;
};

#endif // HEALINGITEM_H
