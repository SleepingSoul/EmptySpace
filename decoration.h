#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsItem>
#include <QPainter>

class Decoration : public QGraphicsItem
{
public:
    explicit Decoration(QPolygon = QPolygon(QRect(0, 0, 50, 50)));
    ~Decoration();
    void set_polygon(QPolygon);
    QPolygon Polygon() const;
    void set_def_pos(const QPoint);
    QPoint def_pos() const;
private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    QPolygon form;

    QPainterPath _shape_path;                       //for optimisation of shape() func
    QRectF _bounding_rect;                          //for optimisation of boundingRect() func
    QPoint _default_pos;
};

#endif // DECORATION_H
