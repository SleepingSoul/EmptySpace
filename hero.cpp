#include "hero.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    //function makes angle from 0 to TwoPi
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Hero::Hero(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    is_moving(false),
    _thrust_offset(0)
{
    hero_pic = new QPixmap("spaceship_pic150x150.png");
    sprite_thrust = new QPixmap("thrust_sprite_blue.png");
}

Hero::~Hero()
{
    delete hero_pic;
    delete sprite_thrust;
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
    //Paint hero (triangle in this case)
    if (is_moving) {
        QPixmap thrust_pic;
        QRect cut_rect;

        if (_thrust_offset / 30 > 9)
            cut_rect.setRect(270, 0, 30, 70);
        else {
            cut_rect.setRect(_thrust_offset, 0, 30, 70);
            _thrust_offset += 30;
        }

        thrust_pic = sprite_thrust->copy(cut_rect);

        QRect thrust_rect1(-30, 0, 30, 70);

        painter->drawPixmap(-17, 15, 30, 70, thrust_pic);
        is_moving = false;
    }
    else {
        QPixmap thrust_pic;
        QRect cut_rect;
        if (_thrust_offset / 30 >= 0) {
            cut_rect.setRect(_thrust_offset, 0, 30, 70);
            _thrust_offset -= 30;
            thrust_pic = sprite_thrust->copy(cut_rect);
            painter->drawPixmap(-17, 30, 30, 70, thrust_pic);
        }
        else {
            cut_rect.setRect(0, 0, 30, 70);
            thrust_pic = sprite_thrust->copy(cut_rect);
            painter->drawPixmap(-17, 30, 30, 70, thrust_pic);
        }
    }
    painter->drawPixmap(-75, -75, 150, 150, *hero_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Hero::slotSetMovingState(bool state_flag)
{
    is_moving = state_flag;
}

void Hero::slotSetDirection(dir d)
{
    direction = d;
}
