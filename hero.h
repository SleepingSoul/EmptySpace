#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QSet>
#include "gameplaymovableitem.h"

class QTimer;
class Gun;
class HeroThrust;
class QMediaPlayer;
class Shield;

class Hero : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

    void stopTime() override;
    void startTime() override;
    void getDamage(const int) override;
    int type() const override;

    void changeWeapon();
    void charge();
    void activateShield();

signals:
    void moveBackground(qreal);
    void signalHpChanged(int);
    void signalCharged();

public slots:
    void slotTarget();
    void slotShot  (bool);

private slots:
    void slotHeroTimer();
    void slotButtons  (QSet <Qt::Key> &);
    void slotChargeEnded();
    void slotCharged();
    void slotShieldExpired();

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;
    QVariant itemChange(GraphicsItemChange, const QVariant &)                    override;

    void moveSystem(const QPointF &);
    void updateThrustsPos();

private /*objects*/:
    QMediaPlayer   *player;
    QPixmap        *hero_pic;
    QTimer         *ptimer;
    QTimer         *charge_timer;
    QPointF        target;
    Gun            *pgun;
    Shield         *shield {nullptr};
    QSet <Qt::Key> keys;
    HeroThrust     *left_th;
    HeroThrust     *right_th;
    const int      STEP {4};
    int hp         {1000};
    int step {3};
    int default_step {3};
    int charged_step {8};
    bool can_charge {true};
    bool can_activate_shield {true};
    bool has_shield {false};
};

#endif // HERO_H
