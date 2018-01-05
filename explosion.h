#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include "gameplayitem.h"

class QTimer;
class QPixmap;
class QPainter;

class Explosion : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = 0);
    ~Explosion();

    int type() const override;

    /*Start/stop all timers*/
    void stopTime () override;
    void startTime() override;

protected slots:
    virtual void nextFrame();

protected /*functions*/:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

protected /*objects*/:
    QTimer  *timer;
    QPixmap *spriteImage;
    int     currentFrame;
};

#endif // EXPLOSION_H
