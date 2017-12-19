#ifndef HPLINE_H
#define HPLINE_H

#include "gameplayitem.h"
#include <QGraphicsItem>

class HpLine : public QGraphicsItem, public GameplayItem
{
public:
    enum {Type = UserType + 1};

    HpLine();
    ~HpLine();

    int type() const override
    {
        return Type;
    }

    void stopTime() override {}
    void startTime() override {}

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // HPLINE_H
