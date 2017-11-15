#include "decoration.h"

Decoration::Decoration(QRect r)
    : QGraphicsItem()
{
    rect = r;
}

Decoration::~Decoration()
{

}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::darkGray));
    painter->drawRect(rect);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Decoration::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

QRectF Decoration::boundingRect() const
{
    return rect;
}

QRect Decoration::Rect() const
{
    return rect;
}
