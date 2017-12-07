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
#include "bullet.h"
#include "direction.h"
#include "project_math.h"
class Gun;

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

signals:
    void moveBackground(dir);
    void moveBackground(qreal);

public slots:
    void slotTarget(QPointF);
    void slotShot  (bool);

private slots:
    void slotHeroTimer();
    void slotButtons  (QSet <Qt::Key> &);

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;
    QVariant itemChange(GraphicsItemChange, const QVariant &)                    override;

private /*objects*/:
    QPixmap *   hero_pic;
    QTimer *    ptimer;
    QTimer *    pshoting_timer;
    QPointF     target;
    HeroThrust *pthrust;
    Gun        *pgun;
    QSet <Qt::Key> keys;
    const int   STEP {4};
};

#endif // HERO_H
