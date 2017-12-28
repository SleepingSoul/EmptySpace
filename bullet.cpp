#include "bullet.h"
#include <math.h>
#include "project_math.h"
#include <QTimer>
#include <QPainter>
#include <QGraphicsScene>
#include "explosion.h"

Bullet::Bullet(const int d, const int sm, QPixmap *bullet_pic, GameplayMovableItem *s, QObject *parent)
    : QObject(parent),
      bulletPic(bullet_pic),
      sender(s),
      damage(d),
      single_move(sm)
{
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotTimerBullet()));
    has_hero_sender = s->isHeroType();
}

Bullet::~Bullet()
{

}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-15, -15, 30, 30, *bulletPic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Bullet::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Bullet::slotTimerBullet()
{
    bool should_be_destroyed{false};

    this->setPos(mapToParent(0, -single_move));

    if (this->collidesWithImpassableItem()) {
        Explosion *exp = new Explosion;
        exp->setPos(this->pos());
        scene()->addItem(exp);
        should_be_destroyed = true;
    }
    else if (this->collidesWithDamagebleItem() &&
             !(this->collidesWithDamagebleItem()->isHeroType() && has_hero_sender))
    {
        this->collidesWithDamagebleItem()->getDamage(this->damage);
        Explosion *exp = new Explosion;
        exp->setPos(this->pos());
        scene()->addItem(exp);
        should_be_destroyed = true;
    }

    /*Check out of scene bullets*/
    if (!this->isInView())
        should_be_destroyed = true;

    if (should_be_destroyed)
        this->deleteLater();
}

int Bullet::Damage() const
{
    return damage;
}

QVariant Bullet::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {    //value = scene ptr
        ptimer->start(_timerTemp_ms);
    }
    return QGraphicsItem::itemChange(change, value);
}

int Bullet::type() const
{
    return SimpleType;
}

void Bullet::stopTime()
{
    ptimer->stop();
}

void Bullet::startTime()
{
    ptimer->start(_timerTemp_ms);
}
