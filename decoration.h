#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsItem>
#include <QPainter>
#include "gameplayitem.h"

/*Parent classes:
 * QGraphicsItem: for placing on the scene;
 * GameplayItem: to eneble/disable timers */

class Decoration : public QGraphicsItem, public GameplayItem
{
public:
    explicit Decoration(QPolygon);
    ~Decoration();
    //void set_polygon(QPolygon);
    //QPolygon Polygon() const;
    //void set_def_pos(const QPoint);
    //QPoint def_pos  () const;

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
