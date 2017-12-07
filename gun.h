#ifndef GUN_H
#define GUN_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <cassert>
#include "direction.h"
class QTimer;
class QPixmap;

class Gun : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Gun(QObject *parent = 0);\
    ~Gun();
    void shoot(const bool);

public slots:
    void slotTarget(QPointF);
    void setTarget(const QPointF);

private /*objects*/:
    QTimer *timer;
    QTimer *shooting_timer;
    QPixmap *bullet_pic;
    QPointF target;
    QPixmap *pic;
    int     shot_interval {220};

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

private slots:
    void slotTwirl();
    void slotShooting();
};

#endif // GUN_H
