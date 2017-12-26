#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "gameplayitem.h"

class QPixmap;

class InfoWindow : public GameplayItem
{
public:
    InfoWindow(const int, const int);
    ~InfoWindow();

    void stopTime() override;
    void startTime() override;

    void setInfoText(const char *);
    int Width() const;
    int Height() const;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    QPixmap *bg_image;
    QString info_str;
    const int width;
    const int height;
};

#endif // INFOWINDOW_H
