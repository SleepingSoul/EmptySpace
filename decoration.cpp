#include "decoration.h"

Decoration::Decoration(QPolygon poly)
{
    form = poly;
    _shape_path.addPolygon(poly);
    _bounding_rect = form.boundingRect();

//    /*brush texture set up*/
//    brush.setTexture(QPixmap("texture_decs.png"));
//    pen.setBrush(QBrush(QPixmap("industrial.jpg")));
//    pen.setWidth(10);
}

Decoration::~Decoration()
{

}

int Decoration::type() const
{
    return +ImpassableType;
}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(brush);
//    painter->setPen(pen);
//    painter->drawPolygon(form);
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

//QPolygon Decoration::Polygon() const
//{
//    return form;
//}

//void Decoration::set_def_pos(const QPoint p)
//{
//    _default_pos = p;
//}

//QPoint Decoration::def_pos() const
//{
//    return _default_pos;
//}
