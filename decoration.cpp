#include "decoration.h"

Decoration::Decoration(QPolygon poly)
    : QGraphicsItem()
{
    form = poly;
    _shape_path.addPolygon(poly);
    _bounding_rect = form.boundingRect();
}

Decoration::~Decoration()
{

}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::darkGray));
    painter->drawPolygon(form);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Decoration::shape() const
{
    return _shape_path;
}

QRectF Decoration::boundingRect() const
{
    return _bounding_rect;
}

QPolygon Decoration::Polygon() const
{
    return form;
}
