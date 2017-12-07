#include "bullet.h"
#include <math.h>
#include "project_math.h"

Bullet::Bullet(const int d, QPixmap *bullet_pic, QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
      bulletPic(bullet_pic)
{
    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotTimerBullet()));
    Q_UNUSED(d); //yet
}

Bullet::~Bullet()
{

}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-15, -15, 30, 30, *bulletPic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Bullet::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Bullet::slotTimerBullet()
{
    this->setPos(mapToParent(0, -7));

    /** Производим проверку на то, наткнулась ли пуля на какой-нибудь
     * элемент на графической сцене.
     * Для этого определяем небольшую область перед пулей,
     * в которой будем искать элементы
     * */
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-1, -1)
                                                       << mapToScene(1, -1));
    /** После чего проверяем все элементы.
     * Одними из них будут сама Пуля и Герой - с ними ничего не делаем.
     * А с остальными вызываем CallBack функцию
     * */
    foreach (QGraphicsItem *item, foundItems) {
        /*Check items. If item is bullet or explosion,
         * then not explode. Otherwise make explosion.*/
        if (item == this || item->type() == (UserType + 1))
            continue;

        Explosion *exp = new Explosion;
        exp->setPos(this->pos());
        scene()->addItem(exp);
        this->deleteLater();
    }

    /*Check out of scene bullets*/
    if (!scene()->sceneRect().contains(this->pos()))
        this->deleteLater();
}

int Bullet::Damage() const
{
    return damage;
}

QVariant Bullet::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {    //value = scene ptr
        ptimer->start(_timerTemp_ms);
    }
    return QGraphicsItem::itemChange(change, value);
}

int Bullet::type() const
{
    return Type;
}