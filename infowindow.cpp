#include "infowindow.h"
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <gamescene.h>

InfoWindow::InfoWindow(const int w, const int h, QObject *parent)
    : width(w), height(h), QObject(parent), offset(w)
{
    font.setPointSize(8);
    font.setFamily("Lucida Console");
    bg_image = new QPixmap("media/info_window_bg.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimer()));
}

InfoWindow::~InfoWindow()
{
    delete bg_image;
}

void InfoWindow::stopTime()
{
    timer->stop();
}

void InfoWindow::startTime()
{
    timer->start(18);
}

int InfoWindow::type() const
{
    return SimpleType;
}

void InfoWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPixmap(0 + width - offset, 0, width, height, *bg_image);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRectF(20 + width - offset, 20, width - 50, height - 50), info_str);

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

void InfoWindow::slotTimer()
{
    if (++_counter >= 80) {
        offset -= 2;
        if (offset <= 0) {
            timer->stop();
            dynamic_cast <GameScene *>(scene())->popInfoWindow();
            this->deleteLater();
        }
    }
}

QVariant InfoWindow::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {
        timer->start(18);
    }
    return QGraphicsItem::itemChange(change, value);
}
