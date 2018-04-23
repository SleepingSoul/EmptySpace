#include "flamestream.h"
#include <QPixmap>
#include <QPainter>
#include <QTimer>

FlameStream::FlameStream(QObject *parent)
    : QObject(parent)
{
    blaster_sprite = new QPixmap("media/shooting_sp.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotFrame()));
}

FlameStream::~FlameStream()
{
    delete blaster_sprite;
}

void FlameStream::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!shooting)
        return;
    else {
        if (current_frame == 0) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(0, 0, 30, 60));
        }
        else if (current_frame == 1) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(30, 0, 30, 60));
        }
        else if (current_frame == 2){
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(60, 0, 30, 60));
        }
        else if (current_frame == 3) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(90, 0, 30, 60));
        }
        else if (current_frame == 4) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(120, 0, 30, 60));
        }
        else if (current_frame == 5) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(150, 0, 30, 60));
        }
        else if (current_frame == 6) {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(180, 0, 30, 60));
        }
        else {
            painter->drawPixmap(-20, -30, 40, 60, blaster_sprite->copy(210, 0, 30, 60));
        }
    }
}

void FlameStream::shootCall(const bool f)
{
    if (f) {
        timer->start(30);
        shooting = true;
    }
    else {
        timer->stop();
        shooting = false;
    }
}

QRectF FlameStream::boundingRect() const
{
    return QRectF(-20, -60, 40, 220);
}

void FlameStream::slotFrame()
{
    ++current_frame %= 8;
}
