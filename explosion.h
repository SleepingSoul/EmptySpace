#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsItem>
#include "gameplayitem.h"

class QTimer;
class QPixmap;
class QPainter;

/*Parent classes:
 * QObject: for signals/slots;
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Explosion : public QObject, public QGraphicsItem, public GameplayItem
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = 0);
    ~Explosion();

    enum {Type = UserType + 1};
    int type() const;

    /*Start/stop all timers*/
    void stopTime () override;
    void startTime() override;

private slots:
    void nextFrame();

private /*functions*/:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

private /*objects*/:
    QTimer  *timer;
    QPixmap *spriteImage;
    int     currentFrame;
};

#endif // EXPLOSION_H
