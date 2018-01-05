#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QObject>
#include <QFont>
#include "gameplayitem.h"

class QPixmap;
class QTimer;

class InfoWindow : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit InfoWindow(const int, const int, QObject * = 0);
    ~InfoWindow();

    void stopTime() override;
    void startTime() override;
    int type() const override;

    void setInfoText(const char *);
    int Width() const;
    int Height() const;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QTimer *timer;
    QPixmap *bg_image;
    QString info_str;
    QFont font;
    const int width;
    const int height;
    unsigned short offset {200};
    unsigned short _counter {0};

private slots:
    void slotTimer();
};

#endif // INFOWINDOW_H
