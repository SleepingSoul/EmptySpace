#include "quitwindow.h"
#include <QPainter>
#include "sizes.h"

QuitWindow::QuitWindow()
     : QGraphicsItem()
{
    pic = new QPixmap("panel_bg.png");
}

QuitWindow::~QuitWindow()
{
    delete pic;
}

void QuitWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawPixmap(pic->width() / -2, pic->height() / -2, pic->width(), pic->height(), *pic);
}

QRectF QuitWindow::boundingRect() const
{
    return QRectF(pic->width() / -2, pic->height() / -2, pic->width(), pic->height());
}

int QuitWindow::width() const
{
    return pic->width();
}

int QuitWindow::height() const
{
    return pic->height();
}
