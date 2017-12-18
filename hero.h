#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QSet>
#include "gameplayitem.h"

class QTimer;
class Gun;
class HeroThrust;

/*Parent classes:
 * QObject: for signals/slots;
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Hero : public QObject, public QGraphicsItem, public GameplayItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

    void stopTime() override;
    void startTime() override;

signals:
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

    void moveSystem(const QPointF &);
    void updateThrustsPos();

private /*objects*/:
    QPixmap        *hero_pic;
    QTimer         *ptimer;
    QTimer         *pshoting_timer;
    QPointF        target;
    Gun            *pgun;
    QSet <Qt::Key> keys;
    HeroThrust     *left_th;
    HeroThrust     *right_th;
    const int      STEP {4};
};

#endif // HERO_H
