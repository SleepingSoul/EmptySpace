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

using WeaponOptions::Blaster;
using WeaponOptions::Plasma;

Gun::Gun(GameplayMovableItem *h, QObject *parent)
    : QObject(parent),
      hero(h)
{
    pic = new QPixmap("media/tower.png");
    blaster_bullet_pic = new QPixmap("media/bullet_1.png");
    plasma_bullet_pic = new QPixmap("media/bullet_2.png");
    timer = new QTimer(this);
    shooting_timer = new QTimer();
    connect(shooting_timer, SIGNAL(timeout()), SLOT(slotShooting()));
    connect(timer,          SIGNAL(timeout()), SLOT(slotTwirl()));
    player = new QMediaPlayer;
    player->setVolume(60);
    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);
    fs = new FlameStream(this);
    fs->setPos(mapToParent(0, -80));
    timer->start(18);

    blaster_sound = new QMediaContent(QUrl::fromLocalFile("media/shoot_sound.wav"));
    plasma_sound = new QMediaContent(QUrl::fromLocalFile("media/plasma_sound.wav"));

    playlist->addMedia(*blaster_sound);
    playlist->setCurrentIndex(0);

    options.damage = 40;
    options.bullet_pic = blaster_bullet_pic;
    options.shot_interval = blaster_shot_interval;
    options.has_dispersion = false;
    options.single_move = 8;
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
        shooting_timer->start(options.shot_interval);
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
    Bullet *bullet = new Bullet(options.damage, options.single_move, options.bullet_pic, hero);
    bullet->setPos(mapToParent(0, -100));
    bullet->setRotation(this->rotation() +
                        (options.has_dispersion? qPow(-1, qrand()) * (qrand() % 5) : 0));
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

void Gun::changeWeapon()
{
    static bool w{true};
    if (!w) {
        options.bullet_pic = blaster_bullet_pic;
        options.damage = blaster_damage;
        options.shot_interval = blaster_shot_interval;
        options.has_dispersion = false;
        playlist->removeMedia(0);
        playlist->addMedia(*blaster_sound);
        options.single_move = 8;
        w = true;
    }
    else {
        options.bullet_pic = plasma_bullet_pic;
        options.damage = plasma_damage;
        options.shot_interval = plasma_shot_interval;
        options.has_dispersion = true;
        playlist->removeMedia(0);
        playlist->addMedia(*plasma_sound);
        options.single_move = 6;
        w = false;
    }
}
