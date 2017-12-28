#include "hero.h"
#include "project_math.h"
#include "sizes.h"
#include "gun.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QCursor>
#include <herothrust.h>
#include "bullet.h"
#include "direction.h"
#include "project_math.h"
#include <QMediaPlayer>
#include "shield.h"

Hero::Hero(QObject *parent)
    : QObject(parent)
{
    hero_pic = new QPixmap("spaceship.png");
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotHeroTimer()));

    charge_timer = new QTimer(this);
    connect(charge_timer, SIGNAL(timeout()), SLOT(slotChargeEnded()));

    player = new QMediaPlayer(this);
    player->setMedia(QMediaContent(QUrl::fromLocalFile("charging.wav")));

    left_th = new HeroThrust;
    right_th = new HeroThrust;
    left_th->setZValue(1);
    right_th->setZValue(1);

    can_activate_shield = true;
}

Hero::~Hero()
{
    delete hero_pic;
}

QRectF Hero::boundingRect() const
{
    //bounding rect of hero
    return QRectF(-60, -80, 120, 160);
}

QPainterPath Hero::shape() const
{
    //Shape of hero (ellipse in this case)
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(hero_pic->width() / -2, hero_pic->height() / -2, hero_pic->width(),
                        hero_pic->height(), *hero_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Hero::slotHeroTimer()
{

    if (!keys.empty()) {
        left_th->setMoving(true);
        right_th->setMoving(true);
    }
    else {
        left_th->setMoving(false);
        right_th->setMoving(false);
    }

    /*Current scene rect*/
    auto cur_rect = scene()->views().front()->sceneRect();
    /*Currect view ptr*/
    auto view = scene()->views().front();
    /*Current hero angle*/
    qreal angle = normalizeDegrees(this->rotation());

    /*We move spaceship depends of current key set*/
    if (keys.contains(Qt::Key_W)) {
        moveSystem({0, -step});
        if (!this->collidesWithImpassableItem())
        {
            view->setSceneRect(cur_rect.translated(step*qSin(qDegreesToRadians(angle)),
                                                   -step*qCos(qDegreesToRadians(angle))));
        }
        else
            moveSystem({0, step});
    }
    if (keys.contains(Qt::Key_S)) {
        moveSystem({0, step});
        if (!this->collidesWithImpassableItem())
            view->setSceneRect(cur_rect.translated(-step*qSin(qDegreesToRadians(angle)),
                                                   step*qCos(qDegreesToRadians(angle))));
        else
            moveSystem({0, -step});
    }
    if (keys.contains(Qt::Key_A)) {
        this->setRotation(this->rotation() - 1);
        updateThrustsPos();
        if (this->collidesWithImpassableItem()) {
            this->setRotation(this->rotation() + 1);
            updateThrustsPos();
        }
    }
    if (keys.contains(Qt::Key_D)) {
        this->setRotation(this->rotation() + 1);
        updateThrustsPos();
        if (this->collidesWithImpassableItem()) {
            this->setRotation(this->rotation() - 1);
            updateThrustsPos();
        }
    }

    auto bonus_item = this->collidesWithBonusItem();

    if (bonus_item && bonus_item->type() == HealingType) {
        qDebug() << "this is gonna be here";
        scene()->removeItem(bonus_item);
        delete bonus_item;
        hp += 100;
        if (hp > 1000)
            hp = 1000;
        emit signalHpChanged(hp);
    }

    /*We always move Gun with our spaceship*/
    pgun->setPos(mapToScene(0, 40));

    if (has_shield)
        shield->setPos(this->pos());
}

void Hero::moveSystem(const QPointF &point)
{
    //point is in this item's coordinate system
    this->setPos(mapToParent(point));
    left_th->setPos(mapToParent(point.x() - 30, point.y() + 100));
    right_th->setPos(mapToParent(point.x() + 30, point.y() + 100));
    updateThrustsPos();
}

void Hero::updateThrustsPos()
{
    left_th->setPos(mapToParent(-30, 100));
    right_th->setPos(mapToParent(30, 100));

    left_th->setRotation(this->rotation());
    right_th->setRotation(this->rotation());
    if (keys.contains(Qt::Key_S)) {
        left_th->setPos(mapToParent(-55, -50));
        right_th->setPos(mapToParent(55, -50));
        left_th->setRotation(180 + this->rotation());
        right_th->setRotation(180 + this->rotation());
    }

    if (keys.contains(Qt::Key_A)) {
        left_th->setRotation(left_th->rotation() + 30);
        left_th->setPos(mapToParent(-50, 105));
        if (keys.contains(Qt::Key_S))
            left_th->setPos(mapToParent(-35, -50));
    }
    else if (keys.contains(Qt::Key_D)) {
        right_th->setRotation(left_th->rotation() - 30);
        right_th->setPos(mapToParent(50, 105));
        if (keys.contains(Qt::Key_S))
            right_th->setPos(mapToParent(35, -50));
    }
}

void Hero::slotTarget()
{
    pgun->updateTarget();
}

QVariant Hero::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        /*value is the new scene.
         * Allocating memory for children, adding
         * them on this scene*/

        pgun = new Gun(this);
        pgun->setZValue(3);
        pgun->setPos(mapToScene(0, 40));
        value.value <QGraphicsScene *>()->addItem(pgun);

        value.value <QGraphicsScene *>()->addItem(left_th);
        value.value <QGraphicsScene *>()->addItem(right_th);

        moveSystem({0, 0});
        updateThrustsPos();

        ptimer->start(18);

    }
    return QGraphicsItem::itemChange(change, value);
}

void Hero::slotShot(bool f)
{
    pgun->shoot(f);
}

void Hero::slotButtons(QSet<Qt::Key> &keyset)
{
    keys = keyset;
}

void Hero::stopTime()
{
    ptimer->stop();
}

void Hero::startTime()
{
    keys.clear();
    ptimer->start(18);
}

void Hero::getDamage(const int damage)
{
    hp -= damage;
    emit signalHpChanged(hp);
}

int Hero::type() const
{
    return HeroType;
}

void Hero::changeWeapon()
{
    pgun->changeWeapon();
}

void Hero::charge()
{
    if (can_charge) {
        step = charged_step;
        charge_timer->start(1500);
        player->play();
        can_charge = false;
        emit signalCharged();
    }
}

void Hero::slotChargeEnded()
{
    step = default_step;
}

void Hero::slotCharged()
{
    can_charge = true;
}

void Hero::activateShield()
{
    if (can_activate_shield) {
        can_activate_shield = false;
        shield = new Shield();
        connect(shield, SIGNAL(signalShieldExpired()), SLOT(slotShieldExpired()));
        shield->setPos(this->pos());
        scene()->addItem(shield);
        shield->activate();
        has_shield = true;
    }
}

void Hero::slotShieldExpired()
{
    delete shield;
    has_shield = false;
}
