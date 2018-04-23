#include "warpeffect.h"
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>

unsigned short WarpEffect::number_of_warps = 0;

WarpEffect::WarpEffect(QGraphicsItem *warped, QObject *parent)
    : QObject(parent), warped_item(warped)
{
    ++number_of_warps;
    timer = new QTimer(this);
    sprite_image.load("media/appearing_sprite.png");
    player = new QMediaPlayer(this);
    player->setMedia(QMediaContent(QUrl::fromLocalFile("media/warp_sound.mp3")));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this,   SLOT  (slotMediaStateChanged(QMediaPlayer::State)));
    connect(timer, SIGNAL(timeout()), SLOT(slotNextFrame()));
}

WarpEffect::~WarpEffect()
{
    delete player;
    warped_item->setPos(this->pos());
    this->scene()->addItem(warped_item);
    --number_of_warps;
}

int WarpEffect::type() const
{
    return SimpleType;
}

QRectF WarpEffect::boundingRect() const
{
    return QRectF(-105, -105, 210, 210);
}

void WarpEffect::stopTime()
{
    _paused = true;
    timer->stop();
    player->stop();
}

void WarpEffect::startTime()
{
    _paused = false;
    timer->start(50);
    player->play();
}

void WarpEffect::slotMediaStateChanged(QMediaPlayer::State st)
{
    if (st == QMediaPlayer::StoppedState && !_paused)
        this->deleteLater();
}

void WarpEffect::slotNextFrame()
{
    if (current_frame < 2310)
        current_frame += 210;
}

void WarpEffect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-105,-105, sprite_image, current_frame, 0, 210, 210);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QVariant WarpEffect::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        timer->start(50);
        player->play();
    }
    return QGraphicsItem::itemChange(change, value);
}
