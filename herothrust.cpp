#include "herothrust.h"
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

HeroThrust::HeroThrust(QObject *parent)
    : QObject(parent)
{
    sprite = new QPixmap("media/thrust_sp.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTick()));
}

HeroThrust::~HeroThrust()
{
    delete sprite;
}

QRectF HeroThrust::boundingRect() const
{
    return QRectF(-30, -50, 60, 100);
}

QPainterPath HeroThrust::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void HeroThrust::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (movingNow)
        if (_counter++ < 10)
            painter->drawPixmap(-15, -60, 30, 120, sprite->copy(offset, 0, 30, 120));
        else {
            if (_flag_1 == 0) {
                _direction = true;
                _flag_1 = 1;
                painter->drawPixmap(-15, -60, 30, 120, sprite->copy(180, 0, 30, 120));
            }
            else if (_flag_1 == 1) {
                _flag_1 = _direction? 2 : 0;
                painter->drawPixmap(-15, -60, 30, 120, sprite->copy(210, 0, 30, 120));
            }
            else if (_flag_1 == 2) {
                _flag_1 = _direction? 3 : 1;
                painter->drawPixmap(-15, -60, 30, 120, sprite->copy(240, 0, 30, 120));
            }
            else {
                _direction = false;
                _flag_1 = 2;
                painter->drawPixmap(-15, -60, 30, 120, sprite->copy(270, 0, 30, 120));
            }
        }
    else {
        _counter = 0;
        if (_flag_2 == 0) {
            _flag_2 = 1;
            painter->drawPixmap(-15, -60, 30, 120, sprite->copy(0, 0, 30, 120));
        }
        else {
            _flag_2 = 0;
            painter->drawPixmap(-15, -60, 30, 120, sprite->copy(30, 0, 30, 120));
        }
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QVariant HeroThrust::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        timer->start(30);
    }
    return QGraphicsItem::itemChange(change, value);
}

void HeroThrust::stopTime()
{
    timer->stop();
}

void HeroThrust::startTime()
{
    timer->start(30);
}

void HeroThrust::slotTick()
{
//    if (movingNow && dir) {
//        offset += 30;
//        if (offset == 270)
//            dir = false;
//    }
//    else if (movingNow && !dir){
//        offset -= 30;
//        if (offset == 0)
//            dir = true;
//    }
    if (movingNow) {
        if (offset <= 240)
            offset += 30;
    }
    else {
        if (offset >= 0)
            offset -= 30;
    }
}

void HeroThrust::setMoving(const bool m)
{
    movingNow = m;
}
