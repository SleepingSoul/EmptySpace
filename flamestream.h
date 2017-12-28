#ifndef FLAMESTREAM_H
#define FLAMESTREAM_H

#include <QObject>
#include "gameplayitem.h"

class QTimer;

class FlameStream : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit FlameStream(QObject *parent = 0);
    ~FlameStream();

    void stopTime() override {}
    void startTime() override {}
    void shootCall(const bool);

private /*objects*/:
    /*Current's weapon features*/
    QPixmap *blaster_sprite;
    QPixmap *plasma_sprite;

    bool shooting {false};
    QTimer *timer;
    int current_frame {0};

private /*functions*/:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private slots:
    void slotFrame();
};

#endif // FLAMESTREAM_H
