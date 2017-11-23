#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "explosion.h"

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum destr_type{WITH_EXPLOSION = 0, WITHOUT_EXPLOSION};

    explicit Bullet(const int d, QPixmap *, /*...*/ QObject *parent = 0);
    ~Bullet();
    int Damage()  const;
    QPointF Pos() const;
    QPointF nextPos();

    //void report_destruction(QPair <Bullet::destr_type, Bullet *>);

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)        override;

private /*objects*/:
    QTimer *ptimer;
    const int damage {25};
    QPixmap *bulletPic;

    static const int _timerTemp_ms {17};

private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
