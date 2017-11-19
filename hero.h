#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

/*direction:
 * NORTH, SOUTH, WEST, EAST,
 * NORTHWEST, NORTHEAST,
 * SOUTHWEST, SOUTHEAST,
 * NO_DIR = direction is undefined*/
enum dir{N = 0, S, W, E, NW, NE, SW, SE, NO_DIR};

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

public slots:
    void slotSetMovingState(bool);
    void slotSetDirection(dir);

private:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;   //Paint the hero
    QPainterPath shape() const override;                                            //For collisions
    QPixmap *hero_pic;
    QPixmap *sprite_thrust;
    dir direction;

    int _thrust_offset;
    bool is_moving;
};

#endif // HERO_H
