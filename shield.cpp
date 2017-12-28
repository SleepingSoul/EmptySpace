#include "shield.h"
#include <QTimer>
#include <QPainter>

Shield::Shield(QObject *parent)
    : QObject(parent)
{
    shield_image.load("shield_image.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimer()));
}

Shield::~Shield()
{

}

int Shield::type() const
{
    return HeroType;
}

void Shield::startTime()
{
    if (_timer_was_stoped)
        timer->start(1000);
}

void Shield::stopTime()
{
    if (timer->isActive()) {
        _timer_was_stoped = true;
        timer->stop();
    }
}

void Shield::activate()
{
    timer->start(1000);
}

void Shield::slotTimer()
{
    static int counter(0);
    if (++counter >= 10) {
        timer->stop();
        counter = 0;
        emit signalShieldExpired();
    }
}

void Shield::getDamage(const int d)
{
    hp -= d;
    if (hp <= 0) {
        emit signalShieldExpired();
    }
}

void Shield::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(-shield_image.width()/2.,-shield_image.height()/2., shield_image.width(),
                        shield_image.height(), shield_image);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Shield::boundingRect() const
{
    return QRectF(-shield_image.width()/2.,-shield_image.height()/2., shield_image.width(),
                  shield_image.height());
}

QPainterPath Shield::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
