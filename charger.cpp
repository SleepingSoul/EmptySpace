#include "charger.h"
#include <QTimer>
#include <QPixmap>
#include <QPainter>

Charger::Charger(QObject *parent)
    : QObject(parent)
{
    bg_image_a.load("a_chargers_picture.png");
    bg_image_una.load("una_chargers_picture.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimer()));
}

Charger::~Charger()
{

}

int Charger::type() const
{
    return SimpleType;
}

void Charger::startTime()
{
    if (_timer_was_stoped)
        timer->start(100);
}

void Charger::stopTime()
{
    if (timer->isActive()) {
        _timer_was_stoped = true;
        timer->stop();
    }
}

void Charger::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (state == ChargerIsAvailable) {
        painter->drawPixmap(0, 0, bg_image_a);
    }
    else {
        painter->drawPixmap(0, 0, bg_image_una);
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::green);
        painter->drawRect(50, 70, progress, 10);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Charger::slotTimer()
{
    if (++progress > 100) {
        timer->stop();
        state = ChargerIsAvailable;
        progress = 0;
        emit signalCharged();
    }
}

QRectF Charger::boundingRect() const
{
    return bg_image_a.rect();
}

void Charger::setState(const ChargerState s)
{
    state = s;
    if (s == ChargerUnavailable)
        timer->start(100);
}

void Charger::slotHeroCharged()
{
    if (state == ChargerIsAvailable) {
        state = ChargerUnavailable;
        timer->start(100);
    }
}
