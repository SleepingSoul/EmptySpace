#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QCursor>
#include <windows.h>            //!!!better to change later
#include <herothrust.h>
#include <QGraphicsScene>
#include "bullet.h"
#include "direction.h"
#include "project_math.h"

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

signals:
    void moveBackground(dir);

public slots:
    void slotTarget(QPointF);
    void slotShot  (bool);

private slots:
    void slotHeroTimer();
    void slotTwirl();
    void slotShoting();

private:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)        override;
    QPixmap *hero_pic;
    QTimer  *ptimer;
    QTimer  *pshoting_timer;
    QPointF target;
    HeroThrust *pthrust;
    const int STEP {4};
    int shot_interval {240};
    QPixmap *bulletPic;
};

#endif // HERO_H
