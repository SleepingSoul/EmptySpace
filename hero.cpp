#include "hero.h"
//#include <math.h>

Hero::Hero(QObject *parent) :

    QObject       (parent),
    QGraphicsItem ()
{
    hero_pic = new QPixmap("spaceship_pic150x150.png");
}

Hero::~Hero()
{
    delete hero_pic;
}

QRectF Hero::boundingRect() const
{
    //bounding rect of hero
    return QRectF(-50, -50, 100, 100);
}

QPainterPath Hero::shape() const
{
    //Shape of hero (ellipse in this case)
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-50, -50, 100, 100, *hero_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
