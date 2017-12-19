#ifndef GUN_H
#define GUN_H

#include <QObject>
#include <QGraphicsItem>
#include "gameplayitem.h"

class QTimer;
class QPixmap;
class FlameStream;
class QMediaPlayer;
class QMediaPlaylist;

/* Parent classes:
 * QObject: for signals/slots;
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Gun : public QObject, public QGraphicsItem, public GameplayItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Gun(QObject *parent = 0);\
    ~Gun();
    void shoot(const bool);

    void stopTime() override;
    void startTime() override;

public slots:
    void slotTarget(QPointF);
    void setTarget(const QPointF);

private /*objects*/:
    QTimer *timer;
    QTimer *shooting_timer;
    QPixmap *bullet_pic;
    QPointF target;
    QPixmap *pic;
    FlameStream *fs;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    int     shot_interval {220};

private /*functions*/:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void slotTwirl();
    void slotShooting();
};

#endif // GUN_H
