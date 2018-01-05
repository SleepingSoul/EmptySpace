#include "enemy.h"
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include "project_math.h"
#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "healingitem.h"
#include "characterexplosion.h"

QGraphicsItem *Enemy::hero = nullptr;

void Enemy::setHero(QGraphicsItem *h)
{
    hero = h;
}

Enemy::Enemy(QObject *parent)
    : QObject(parent)
{
    enemy_pic = new QPixmap("spaceship_pic150x150.png");
    bullet_pic = new QPixmap("bullet_3.png");
    timer = new QTimer(this);
    shooting_timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimer()));
    connect(shooting_timer, SIGNAL(timeout()), SLOT(slotShoot()));

    player = new QMediaPlayer;
    player->setVolume(50);
    playlist = new QMediaPlaylist();
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile("shoot_sound.wav")));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    shot_interval = 500;
}

Enemy::~Enemy()
{
    /*Cant delete bullet pic, because bullet can exist after our destruction*/
    delete player;
    delete enemy_pic;
    delete playlist;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-enemy_pic->width()/2., -enemy_pic->height()/2., *enemy_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(-enemy_pic->width()/2., -enemy_pic->height()/2.,
                  enemy_pic->width(), enemy_pic->height());
}

void Enemy::slotTimer()
{
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(hero->scenePos()));

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

    if (this->hp <= 0) {
        timer->stop();
        HealingItem *h_item = new HealingItem;
        h_item->setPos(this->pos());
        scene()->addItem(h_item);

        CharacterExplosion *exp = new CharacterExplosion;
        exp->setPos(this->pos());
        scene()->addItem(exp);
        this->deleteLater();
    }
}

void Enemy::slotShoot()
{
    if (this->isInView()) {
        player->play();
        Bullet *bullet = new Bullet(25, 7, bullet_pic, this);
        bullet->setPos(mapToParent(0, -100));
        bullet->setRotation(this->rotation());
        bullet->setZValue(2);
        scene()->addItem(bullet);
    }
    else
        player->stop();
}

void Enemy::stopTime()
{
    timer->stop();
    shooting_timer->stop();
    player->stop();
}

void Enemy::startTime()
{
    timer->start(17);
    shooting_timer->start(shot_interval);
    player->play();
}

QVariant Enemy::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        /*value is the new scene.
         * Allocating memory for children, adding
         * them on this scene*/

        timer->start(17);
        shooting_timer->start(500);
    }
    return QGraphicsItem::itemChange(change, value);
}

void Enemy::getDamage(const int damage)
{
    this->hp -= damage;
}

int Enemy::type() const
{
    return DamagebleType;
}
