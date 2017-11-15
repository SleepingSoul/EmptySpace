#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsItem>
#include <QPainter>

class Decoration : public QGraphicsItem
{
public:
    explicit Decoration(QRect = QRect(0, 0, 50, 50));
    ~Decoration();
    QRect Rect() const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    QRect rect;
};

#endif // DECORATION_H
