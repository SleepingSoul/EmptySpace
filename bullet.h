#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include <QDebug>
#include "explosion.h"

class Bullet : public QObject, public QGraphicsItem
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

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;
    QVariant itemChange(GraphicsItemChange, const QVariant &)                    override;

private /*objects*/:
    QTimer    *ptimer;
    QPixmap   *bulletPic;
    const int damage {25};

    static const int _timerTemp_ms {15};

private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
