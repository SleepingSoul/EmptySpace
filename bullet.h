#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "gameplaymovableitem.h"

class Bullet : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    explicit Bullet(const int, const int, QPixmap *, GameplayMovableItem * = nullptr, QObject * = 0);
    ~Bullet();

    int type       () const override;

    /*Stop/start all timers*/
    void stopTime () override;
    void startTime() override;

    void getDamage(const int) override {}

private /*functions*/:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QVariant itemChange(GraphicsItemChange, const QVariant &) override;

private /*objects*/:
    /*Global timer for all bullets - for optimisation*/
    static QTimer    *global_bullet_timer;
    QPixmap   *bulletPic;
    GameplayMovableItem *sender;
    const int damage {25};
    const int single_move {7};
    bool has_hero_sender;

    static unsigned short bullet_number;
    static const int _timerTemp_ms {17};

private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
