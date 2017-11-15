#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsItem>
#include <QPainter>

class Decoration : public QGraphicsItem
{
public:
    explicit Decoration(QRect = QRect(0, 0, 50, 50));
    Decoration(QPainterPath);
    ~Decoration();
    void set_path(QPainterPath);
    QPainterPath Path() const;
private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    QPainterPath form;
};

#endif // DECORATION_H
