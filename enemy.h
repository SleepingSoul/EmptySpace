#ifndef ENEMY_H
#define ENEMY_H

#include "gameplaymovableitem.h"
#include <QObject>

class Enemy : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    enum {Type = UserType + 3}; //type of class that can take damage
    explicit Enemy(QObject * = 0);
    ~Enemy();

    void stopTime() override;
    void startTime() override;
    int type() const
    {
        return Type;
    }

    void getDamage(const int) override;

    static void setHero(QGraphicsItem *);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void expire();
    QPixmap *enemy_pic;
    QPixmap *bullet_pic;
    QTimer *timer;
    QTimer *shooting_timer;
    int hp {200};
    static QGraphicsItem *hero;

private slots:
    void slotTimer();
    void slotShoot();
};

#endif // ENEMY_H
