#include "weapon.h"
#include <QPainter>
#include <QTimer>


Weapon::Weapon(QObject *parent)
    : QObject(parent)
{
    bg_image.load("weapon_picture.png");
    weapon_image.load("weapons.png");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotChangeOffset()));

    this->setZValue(5);
}

Weapon::~Weapon()
{

}

void Weapon::stopTime()
{
    if (timer->isActive())
        _was_changed = true;
    timer->stop();
}

void Weapon::startTime()
{
    if (_was_changed)
        timer->start(20);
    _was_changed = false;
}

int Weapon::type() const
{
    return SimpleType;
}

void Weapon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(0, 0, bg_image);
    painter->drawPixmap(20, 105  - offset, weapon_image);
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF Weapon::boundingRect() const
{
    return bg_image.rect();
}

void Weapon::slotChangeOffset()
{
    static bool direction{true};

    if (direction) {
        if (++offset >= 35) {
            timer->stop();
            direction = false;
        }
    }
    else {
        if (--offset <= 0) {
            timer->stop();
            direction = true;
        }
    }
}

void Weapon::changeWeapon()
{
    timer->start(20);
}
