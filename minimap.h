#ifndef MINIMAP_H
#define MINIMAP_H

#include "gameplayitem.h"

class MiniMap : public GameplayItem
{
public:
    MiniMap();
    ~MiniMap();

    int type() const override
    {
        return SimpleType;
    }

    void stopTime() override {}
    void startTime() override {}
    void setHeroPos(QPointF);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPointF hero_pos;
    QPixmap *minimap_pic;

    QPointF mapToMinimap(const QPointF);
};

#endif // MINIMAP_H
