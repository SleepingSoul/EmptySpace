#include "decoration.h"

Decoration::Decoration(QRect r)
    : QGraphicsItem()
{
    form.addRect(r);
}

Decoration::Decoration(QPainterPath path)
    : QGraphicsItem()
{
    form = path;
}

Decoration::~Decoration()
{

}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::darkGray));
    painter->drawPath(form);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Decoration::shape() const
{
    return form;
}

QRectF Decoration::boundingRect() const
{
    return form.boundingRect();
}

QPainterPath Decoration::Path() const
{
    return form;
}
