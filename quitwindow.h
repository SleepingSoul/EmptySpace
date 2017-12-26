#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QGraphicsItem>
#include "gameplayitem.h"

class QPushButton;

class QuitWindow : public GameplayItem
{
public:
    QuitWindow();
    ~QuitWindow();
    int height() const;
    int width() const;

    void stopTime() override {}
    void startTime() override {}

private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const;
    QPixmap *pic;
};

#endif // QUITWINDOW_H
