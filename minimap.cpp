#include "minimap.h"
#include <QPainter>

MiniMap::MiniMap()
{
    minimap_pic = new QPixmap("minimap_picture.png");
    this->setZValue(4);
}

MiniMap::~MiniMap()
{

}

QRectF MiniMap::boundingRect() const
{
    return QRectF(0, 0, 250, 250);
}

void MiniMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPixmap(0, 0, 250, 250, *minimap_pic);
    painter->setBrush(QBrush(Qt::red));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(mapToMinimap(hero_pos), 3, 3);
}

QPointF MiniMap::mapToMinimap(const QPointF point)
{
    return {20.833 + (point.x() * 250. / 10000.) / 250. * 208.333,
            20.833 + (point.y() * 250. / 10000.) / 250. * 208.333};
}

void MiniMap::setHeroPos(QPointF new_pos)
{
    hero_pos = new_pos;
}
