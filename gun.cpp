#include "gun.h"
#include <QTimer>
#include <QPixmap>
#include "project_math.h"
#include "bullet.h"

Gun::Gun(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    pic = new QPixmap("tower.png");
    bullet_pic = new QPixmap("bullet_1.png");
    timer = new QTimer(this);
    shooting_timer = new QTimer();
    connect(shooting_timer, SIGNAL(timeout()), SLOT(slotShooting()));
    connect(timer,          SIGNAL(timeout()), SLOT(slotTwirl()));
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
    if (f) shooting_timer->start(shot_interval);
    else   shooting_timer->stop();
}

void Gun::slotShooting()
{
    Bullet *bullet = new Bullet(25, bullet_pic);
    bullet->setPos(mapToParent(0, -120));
    bullet->setRotation(this->rotation());
    bullet->setZValue(1);
    scene()->addItem(bullet);
}
