#ifndef GUN_H
#define GUN_H

#include <QObject>
#include "gameplaymovableitem.h"
#include "global_enumerations.h"

class QTimer;
class QPixmap;
class FlameStream;
class QMediaPlayer;
class QMediaPlaylist;
class QMediaContent;

/* Parent classes:
 * QObject: for signals/slots;
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Gun : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit Gun(GameplayMovableItem *, QObject *parent = 0);
    ~Gun();
    void shoot(const bool);

    void stopTime() override;
    void startTime() override;
    bool isShooting() const;

    void updateTarget();
    void changeWeapon();

private /*objects*/:
    struct CurrentWeaponOptions {
        int shot_interval;
        int damage;
        int single_move;
        bool has_dispersion {false};
        QPixmap *bullet_pic;
    };

    QTimer *timer;
    QTimer *shooting_timer;
    QPixmap *bullet_pic;
    QPointF target;
    QPixmap *pic;
    FlameStream *fs;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QMediaContent *blaster_sound;
    QMediaContent *plasma_sound;
    GameplayMovableItem *hero;
    bool    is_shooting {false};
    bool    is_paused {false};

    /*Current weapon options*/
    WeaponOptions::WeaponType current_weapon {WeaponOptions::Blaster};
    int     blaster_shot_interval {440};
    int     plasma_shot_interval  {600};
    int     blaster_damage {40};
    int     plasma_damage  {75};
    QPixmap *blaster_bullet_pic;
    QPixmap *plasma_bullet_pic;
    CurrentWeaponOptions options;

private /*functions*/:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void slotTwirl();
    void slotShooting();
};

#endif // GUN_H
