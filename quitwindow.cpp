#include "quitwindow.h"
#include <QPainter>
#include "sizes.h"

QuitWindow::QuitWindow()
     : QGraphicsItem()
{
    pic = new QPixmap("quit_pic.png");
}

QuitWindow::~QuitWindow()
{

}

void QuitWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawPixmap(pic->width() / -2, pic->height() / -2, pic->width(), pic->height(), *pic);
}

QRectF QuitWindow::boundingRect() const
{
    return QRectF(pic->width() / -2, pic->height() / -2, pic->width(), pic->height());
}
