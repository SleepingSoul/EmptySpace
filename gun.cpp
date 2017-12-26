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
#include <QCursor>
#include <QGraphicsView>

Gun::Gun(GameplayMovableItem *h, QObject *parent)
    : QObject(parent),
      hero(h)
{
    pic = new QPixmap("tower.png");
    bullet_pic = new QPixmap("bullet_1.png");
    timer = new QTimer(this);
    shooting_timer = new QTimer();
    connect(shooting_timer, SIGNAL(timeout()), SLOT(slotShooting()));
    connect(timer,          SIGNAL(timeout()), SLOT(slotTwirl()));
    player = new QMediaPlayer;
    player->setVolume(100);
    playlist = new QMediaPlaylist();
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile("shoot_sound.wav")));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    fs = new FlameStream(this);
    fs->setPos(mapToParent(0, -80));
    timer->start(18);
}

Gun::~Gun()
{

}

void Gun::updateTarget()
{
    //a little bit complicated algorithm of determination of current cursor position on the scene
    target = QCursor::pos() + QPointF(scene()->views().front()->sceneRect().topLeft()) - QPointF(2, 90);
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
    painter->drawPixmap(pic->width() / -2, pic->height() / -2, pic->width(), pic->height(), *pic);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Gun::boundingRect() const
{
    return QRectF(-20, -40, 40, 80);
}

void Gun::shoot(const bool f)
{
    if (f && !is_paused) {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->play();
        is_shooting = true;
        slotShooting();             /*instant shot when button pressed*/
        shooting_timer->start(shot_interval);
        fs->shootCall(true);
    }
    else {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        is_shooting = false;
        shooting_timer->stop();
        fs->shootCall(false);
    }
}

void Gun::slotShooting()
{
    Bullet *bullet = new Bullet(25, bullet_pic, hero);
    bullet->setPos(mapToParent(0, -100));
    bullet->setRotation(this->rotation());
    bullet->setZValue(2);
    scene()->addItem(bullet);
}

void Gun::stopTime()
{
    is_paused = true;
    timer->stop();
    shooting_timer->stop();
}

void Gun::startTime()
{
    is_paused = false;
    timer->start(18);
}

QVariant Gun::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        value.value <QGraphicsScene *>()->addItem(fs);
    }
    return QGraphicsItem::itemChange(change, value);
}

bool Gun::isShooting() const
{
    return is_shooting;
}
