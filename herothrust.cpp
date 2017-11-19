#include "herothrust.h"

HeroThrust::HeroThrust(QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
      offset(0),
      moving(false)
{
    sprite = new QPixmap("thrust_sprite_blue.png");
}

HeroThrust::~HeroThrust()
{
    delete sprite;
}

QRectF HeroThrust::boundingRect() const
{
    return QRectF(-15, -35, 30, 70);
}

QPainterPath HeroThrust::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void HeroThrust::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap thrust_pic;
    QRect cut_rect;

    if (moving) {
        if (offset / 30 > 8)
            cut_rect.setRect(270, 0, 30, 140);
        else {
            cut_rect.setRect(offset, 0, 30, 140);
            offset += 30;
        }
        moving = false;
    }
    else {
        if (offset / 30 > 0) {
            cut_rect.setRect(offset, 0, 30, 140);
            offset -= 30;
        }
        else
            cut_rect.setRect(0, 0, 30, 140);
    }

    thrust_pic = sprite->copy(cut_rect);

    switch (direction) {
    case NE:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(45));
        painter->drawPixmap(-1*thrust_pic.width(), 0,
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case SE:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(135));
        painter->drawPixmap(-1*thrust_pic.width(), -1*thrust_pic.height(),
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case SW:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(-135));
        painter->drawPixmap(0, -1*thrust_pic.height(),
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case NW:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(-45));
        painter->drawPixmap(0, 0,
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case E:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(90));
        painter->drawPixmap(-1*thrust_pic.width(), -0.5*thrust_pic.height(),
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case S:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(180));
        painter->drawPixmap(-0.5*thrust_pic.width(), -1 * thrust_pic.height(),
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case W:
        thrust_pic = thrust_pic.transformed(QTransform().rotate(-90));
        painter->drawPixmap(0, -0.5*thrust_pic.height(),
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
        break;
    case N:
        //do nothing
        painter->drawPixmap(-0.5*thrust_pic.width(), 0,
                            thrust_pic.width(), thrust_pic.height(), thrust_pic);
    }
}

void HeroThrust::slotSetDirection(dir d)
{
    direction = d;
}

void HeroThrust::slotSetMoving(bool mf)
{
    moving = mf;
}
