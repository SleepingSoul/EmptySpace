#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsItem>
#include <QPainter>
#include "gameplayitem.h"

/*Parent class:
 * GameplayItem: to place on GameScene */

class Decoration : public GameplayItem
{
public:
    explicit Decoration(QPolygon);
    ~Decoration();

    int type() const override;
    void startTime() override {}    //Decorations is not movable game items, so
    void stopTime() override  {}    //we do not have to do something here.
private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;

    QPolygon form;
    QBrush brush;
    QPen pen;

    /*Optimisation features*/
    QPainterPath _shape_path;                       //for optimisation of shape() func
    QRectF       _bounding_rect;                    //for optimisation of boundingRect() func
};

#endif // DECORATION_H
