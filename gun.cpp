#include "gun.h"
#include <QTimer>
#include <QPixmap>
#include "project_math.h"
#include "bullet.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <cassert>
#include "flamestream.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

Gun::Gun(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    pic = new QPixmap("tower.png");
    bullet_pic = new QPixmap("bullet_1.png");
    timer = new QTimer(this);
    shooting_timer = new QTimer();
    connect(shooting_timer, SIGNAL(timeout()), SLOT(slotShooting()));
    connect(timer,          SIGNAL(timeout()), SLOT(slotTwirl()));
    player = new QMediaPlayer;
    player->setMedia(QMediaContent(QUrl::fromLocalFile("shoot.wav")));
    player->setVolume(100);
    //playlist = new QMediaPlaylist();
    //playlist->addMedia(QMediaContent(QUrl::fromLocalFile("shoot.wav")));
    //playlist->setPlaybackMode(QMediaPlaylist::Loop);
    //player->setPlaylist(playlist);
    fs = new FlameStream(this);
    fs->setPos(mapToParent(0, -80));
    timer->start(18);
}

Gun::~Gun()
{

}

void Gun::slotTarget(QPointF point)
{
    target = point;
}

void Gun::slotTwirl()
{
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;

    angleToTarget = normalizeRadians((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi)
        // Rotate left
        setRotation(rotation() - qMin(angleToTarget * 180 /Pi, 3.0));
    else if (angleToTarget <= TwoPi && angleToTarget > Pi)
        // Rotate right
        setRotation(rotation() + qMin((angleToTarget - TwoPi ) * (-180) /Pi, 3.0));

    //dont forget about flamestream
    fs->setPos(mapToParent(0, -80));
    fs->setRotation(this->rotation());
    fs->setZValue(3);
}

void Gun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(pic->width() / -10, pic->height() / -10, pic->width() / 5, pic->height() / 5, *pic);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Gun::boundingRect() const
{
    return QRectF(-20, -40, 40, 80);
}

void Gun::setTarget(const QPointF point)
{
    target = point;
}

void Gun::shoot(const bool f)
{
    if (f) {
        shooting_timer->start(shot_interval);
        fs->shootCall(true);
    }
    else {
        shooting_timer->stop();
        fs->shootCall(false);
    }
}

void Gun::slotShooting()
{
    player->play();
    Bullet *bullet = new Bullet(25, bullet_pic);
    bullet->setPos(mapToParent(0, -100));
    bullet->setRotation(this->rotation());
    bullet->setZValue(2);
    scene()->addItem(bullet);
}

void Gun::stopTime()
{
    timer->stop();
    shooting_timer->stop();
}

void Gun::startTime()
{
    timer->start(18);
}

QVariant Gun::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        value.value <QGraphicsScene *>()->addItem(fs);
    }
    return QGraphicsItem::itemChange(change, value);
}
