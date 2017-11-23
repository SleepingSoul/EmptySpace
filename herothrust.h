#ifndef HEROTHRUST_H
#define HEROTHRUST_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <cassert>
#include "direction.h"

class HeroThrust : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HeroThrust(QObject *parent = 0);
    ~HeroThrust();

    void setDirection(const dir);
    void setMoving   (const bool);

private /*functions*/:
    QRectF boundingRect()                                                  const override;
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape ()                                                  const override;

private /*objects*/:
    QPixmap *sprite;
    dir direction;
    int offset;
    bool moving;
};

#endif // HEROTHRUST_H
