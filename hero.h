#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QSet>
#include "gameplaymovableitem.h"

class QTimer;
class Gun;
class HeroThrust;

class Hero : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    enum {Type = UserType + 4}; /*hero type*/

    explicit Hero(QObject *parent = 0);
    ~Hero();

    void stopTime() override;
    void startTime() override;
    void getDamage(const int) override;
    int type() const override;

signals:
    void moveBackground(qreal);

public slots:
    void slotTarget();
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
