#include "decoration.h"

Decoration::Decoration(QPolygon poly)
{
    form = poly;
    _shape_path.addPolygon(poly);
    _bounding_rect = form.boundingRect();
}

Decoration::~Decoration()
{

}

int Decoration::type() const
{
    return ImpassableType;
}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
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
