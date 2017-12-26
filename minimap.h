#ifndef MINIMAP_H
#define MINIMAP_H

#include "gameplayitem.h"

class MiniMap : public GameplayItem
{
public:
    enum {Type = UserType + 1};

    MiniMap();
    ~MiniMap();

    int type() const override
    {
        return Type;
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
