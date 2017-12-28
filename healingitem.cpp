#include "healingitem.h"
#include <QPainter>

HealingItem::HealingItem()
{
    pic = new QPixmap("healing_item.png");
}

HealingItem::~HealingItem()
{
    delete pic;
}

void HealingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-pic->width()/2., -pic->height()/2., *pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF HealingItem::boundingRect() const
{
    return QRectF(-pic->width()/2., -pic->height()/2., pic->width(), pic->height());
}

int HealingItem::type() const
{
    return HealingType;
}
