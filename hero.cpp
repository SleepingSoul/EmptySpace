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

Hero::Hero(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    hero_pic = new QPixmap("spaceship.png");
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotHeroTimer()));

    left_th = new HeroThrust;
    right_th = new HeroThrust;
    left_th->setZValue(1);
    right_th->setZValue(1);
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
    static bool activated(false);

    if (!keys.empty()) {
        left_th->setMoving(true);
        right_th->setMoving(true);
        activated = true;
    }
    else {
        left_th->setMoving(false);
        right_th->setMoving(false);
        if (activated) {
//            moveSystem({0, -1});
//            if (scene()->collidingItems(this).size() != 2) {
//                moveSystem({0, 1});
//            }
        }
    }

    /*Current scene rect*/
    auto cur_rect = scene()->views().front()->sceneRect();
    /*Currect view ptr*/
    auto view = scene()->views().front();
    /*Current hero angle*/
    qreal angle = normalizeDegrees(this->rotation());

    /*We move spaceship depends of current key set*/
    if (keys.contains(Qt::Key_W)) {
        moveSystem({0, -3});
        qDebug() << scene()->collidingItems(this).size();
        if (scene()->collidingItems(this).size() == 4) {
            qDebug() << "FKING TRUE!";
            view->setSceneRect(cur_rect.translated(3*qSin(qDegreesToRadians(angle)),
                                                   -3*qCos(qDegreesToRadians(angle))));
        }
        if (scene()->collidingItems(this).size() != 4) {
            moveSystem({0, 3});
        }
    }
    if (keys.contains(Qt::Key_S)) {
        moveSystem({0, 3});
        if (scene()->collidingItems(this).size() == 4)
            view->setSceneRect(cur_rect.translated(-3*qSin(qDegreesToRadians(angle)),
                                                   3*qCos(qDegreesToRadians(angle))));
        if (scene()->collidingItems(this).size() != 4) {
            moveSystem({0, -3});
        }
    }
    if (keys.contains(Qt::Key_A)) {
        this->setRotation(this->rotation() - 1);
        updateThrustsPos();
        if (scene()->collidingItems(this).size() != 4) {
            this->setRotation(this->rotation() + 1);
            updateThrustsPos();
        }
    }
    if (keys.contains(Qt::Key_D)) {
        this->setRotation(this->rotation() + 1);
        updateThrustsPos();
        if (scene()->collidingItems(this).size() != 4) {
            this->setRotation(this->rotation() - 1);
            updateThrustsPos();
        }
    }

    /*We always move Gun with our spaceship*/
    pgun->setPos(mapToScene(0, 40));

//    /*Current scene rect*/
//    auto cur_rect = scene()->views().front()->sceneRect();
//    /*Currect view ptr*/
//    auto view = scene()->views().front();
//    /*Current hero angle*/
//    qreal angle = normalizeDegrees(this->rotation());

//    /*Very complicated alghorithm of camera (view) moving*/
//    if (keys.contains(Qt::Key_S)) {
//        if ((x() < cur_rect.x() + 600                     && !(angle <= 360 && angle >= 180)) ||
//            (x() > cur_rect.x() + cur_rect.width() - 600  && !(angle >= 0 && angle <= 180))  ||
//            (y() < cur_rect.y() + 400                     && !(angle >= 270 && angle <= 360 ||
//                                                               angle >= 0 && angle <= 90)) ||
//            (y() > cur_rect.y() + cur_rect.height() - 400 && !(angle >= 90 && angle <= 270)))
//        {
//            view->setSceneRect(cur_rect.translated(-3*qSin(qDegreesToRadians(angle)),
//                                                   3*qCos(qDegreesToRadians(angle))));
//        }
//    }
//    else {
//        if ((x() < cur_rect.x() + 600                     && angle <= 360 && angle >= 180) ||
//            (x() > cur_rect.x() + cur_rect.width() - 600  && angle >= 0 && angle <= 180)  ||
//            (y() < cur_rect.y() + 400                     && (angle >= 270 && angle <= 360 ||
//                                                             angle >= 0 && angle <= 90)) ||
//            (y() > cur_rect.y() + cur_rect.height() - 400 && (angle >= 90 && angle <= 270)))
//        {
//            view->setSceneRect(cur_rect.translated(3*qSin(qDegreesToRadians(angle)),
//                                                   -3*qCos(qDegreesToRadians(angle))));
//        }
//    }
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

void Hero::slotTarget(QPointF point)
{
    pgun->setTarget(point);
}

QVariant Hero::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        /*value is the new scene.
         * Allocating memory for children, adding
         * them on this scene*/

        pgun = new Gun;
        pgun->setZValue(3);
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
