#include "infowindow.h"
#include <QPainter>
#include <QPixmap>

InfoWindow::InfoWindow(const int w, const int h)
    : width(w), height(h)
{
    bg_image = new QPixmap("info_window_bg.png");
}

InfoWindow::~InfoWindow()
{
    delete bg_image;
}

void InfoWindow::stopTime()
{

}

void InfoWindow::startTime()
{

}

void InfoWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0, 0, width, height, *bg_image);
    painter->setPen(QPen(Qt::white));
    QFont font;
    font.setPointSize(12);
    font.setFamily("Lucida Console");
    painter->setFont(font);
    painter->drawText(QRectF(50, 50, width - 100, height - 200), info_str);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF InfoWindow::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

int InfoWindow::Width() const
{
    return width;
}

int InfoWindow::Height() const
{
    return height;
}

void InfoWindow::setInfoText(const char *string)
{
    info_str = string;
}
