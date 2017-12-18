#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include "gameplayitem.h"

/*Parent classes:
 * QObject: for signals/slots;
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Bullet : public QObject, public QGraphicsItem, public GameplayItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum {Type = UserType + 1};

    explicit Bullet(const int, QPixmap *, QObject * = 0);
    ~Bullet();

    int Damage     () const;
    QPointF Pos    () const;
    QPointF nextPos();
    int type       () const override;

    /*Stop/start all timers*/
    void stopTime () override;
    void startTime() override;

private /*functions*/:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QVariant itemChange(GraphicsItemChange, const QVariant &) override;

private /*objects*/:
    QTimer    *ptimer;
    QPixmap   *bulletPic;
    const int damage {25};

    /*All bullets if flying with same speed (maybe, no?)*/
    static const int _timerTemp_ms {15};

private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
