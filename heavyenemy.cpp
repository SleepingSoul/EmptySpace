#include "heavyenemy.h"
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

HeavyEnemy::HeavyEnemy()
{
    enemy_pic = new QPixmap("m_falcon.png");
    bullet_pic = new QPixmap("bullet_4.png");
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
    hp = 1000;
    shot_interval = 1000;
}

HeavyEnemy::~HeavyEnemy()
{

}

QRectF HeavyEnemy::boundingRect() const
{
    return QRectF(-enemy_pic->width()/2., -enemy_pic->height()/2.,
                  enemy_pic->width(), enemy_pic->height());
}

void HeavyEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-enemy_pic->width()/2., -enemy_pic->height()/2., *enemy_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void HeavyEnemy::slotShoot()
{
    if (this->isInView()) {
        player->play();
        Bullet *bullet = new Bullet(75, 10, bullet_pic, this);
        bullet->setPos(mapToParent(0, -190));
        bullet->setRotation(this->rotation());
        bullet->setZValue(2);
        scene()->addItem(bullet);
    }
    else
        player->stop();
}

void HeavyEnemy::slotTimer()
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

    this->setPos(mapToParent(0, -1));
    if (this->collidesWithImpassableItem()) {
        this->setPos(mapToParent(0, 1));
    }

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
