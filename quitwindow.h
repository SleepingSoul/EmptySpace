#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QGraphicsItem>

class QuitWindow : public QGraphicsItem
{
public:
    QuitWindow();
    ~QuitWindow();

private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const;
    QPixmap *pic;

};

#endif // QUITWINDOW_H
