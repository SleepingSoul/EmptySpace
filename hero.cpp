#include "hero.h"
#include "project_math.h"
#include "sizes.h"
#include "gun.h"
#include <QGraphicsView>
#include "project_math.h"

Hero::Hero(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    setRotation(0);
    hero_pic = new QPixmap("spaceship.png");
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotHeroTimer()));
}

Hero::~Hero()
{
    delete hero_pic;
}

QRectF Hero::boundingRect() const
{
    //bounding rect of hero
    return QRectF(-30, -60, 60, 120);
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
    painter->drawPixmap(hero_pic->width() / -10, hero_pic->height() / -10, hero_pic->width() / 5,
                        hero_pic->height() / 5, *hero_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Hero::slotHeroTimer()
{
    /*We move spaceship depends of current key set*/
    if (keys.contains(Qt::Key_W)) {
        this->setPos(mapToParent(0, -3));
        if (scene()->collidingItems(this).size() != 1) {
            this->setPos(mapToParent(0, 3));
        }
    }
    if (keys.contains(Qt::Key_S)) {
        this->setPos(mapToParent(0, 3));
        if (scene()->collidingItems(this).size() != 1) {
            this->setPos(mapToParent(0, -3));
        }
    }
    if (keys.contains(Qt::Key_A)) {
        this->setRotation(this->rotation() - 1);
        if (scene()->collidingItems(this).size() != 1) {
            this->setRotation(this->rotation() + 1);
        }
    }
    if (keys.contains(Qt::Key_D)) {
        this->setRotation(this->rotation() + 1);
        if (scene()->collidingItems(this).size() != 1) {
            this->setRotation(this->rotation() - 1);
        }
    }

    /*We always move Gun with our spaceship*/
    pgun->setPos(mapToScene(0, 40));

    /*Current scene rect*/
    auto cur_rect = scene()->views().front()->sceneRect();
    /*Currect view ptr*/
    auto view = scene()->views().front();
    /*Current hero angle*/
    qreal angle = normalizeDegrees(this->rotation());

    /*Very complicated alghorithm of camera (view) moving*/
    if (keys.contains(Qt::Key_W)) {
        if ((x() < cur_rect.x() + 600                     && angle <= 360 && angle >= 180) ||
            (x() > cur_rect.x() + cur_rect.width() - 600  && angle >= 0 && angle <= 180)  ||
            (y() < cur_rect.y() + 400                     && (angle >= 270 && angle <= 360 ||
                                                             angle >= 0 && angle <= 90)) ||
            (y() > cur_rect.y() + cur_rect.height() - 400 && (angle >= 90 && angle <= 270)))
        {
            view->setSceneRect(cur_rect.translated(3*qSin(qDegreesToRadians(angle)),
                                                   -3*qCos(qDegreesToRadians(angle))));
        }
    }
    else if (keys.contains(Qt::Key_S)) {
        if ((x() < cur_rect.x() + 600                     && !(angle <= 360 && angle >= 180)) ||
            (x() > cur_rect.x() + cur_rect.width() - 600  && !(angle >= 0 && angle <= 180))  ||
            (y() < cur_rect.y() + 400                     && !(angle >= 270 && angle <= 360 ||
                                                               angle >= 0 && angle <= 90)) ||
            (y() > cur_rect.y() + cur_rect.height() - 400 && !(angle >= 90 && angle <= 270)))
        {
            view->setSceneRect(cur_rect.translated(-3*qSin(qDegreesToRadians(angle)),
                                                   3*qCos(qDegreesToRadians(angle))));
        }
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
        pgun->setZValue(2);
        value.value <QGraphicsScene *>()->addItem(pgun);
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
