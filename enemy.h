#ifndef ENEMY_H
#define ENEMY_H

#include "gameplaymovableitem.h"
#include <QObject>

class QMediaPlayer;
class QMediaPlaylist;

class Enemy : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    explicit Enemy(QObject * = 0);
    ~Enemy();

    void stopTime() override;
    void startTime() override;
    int type() const override;

    void getDamage(const int) override;

    static void setHero(QGraphicsItem *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void expire();
    QPixmap *enemy_pic;
    QPixmap *bullet_pic;
    QTimer *timer;
    QTimer *shooting_timer;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    int hp {200};
    int shot_interval;
    static QGraphicsItem *hero;

private slots:
    virtual void slotTimer();
    virtual void slotShoot();
};

#endif // ENEMY_H
