#ifndef WARPEFFECT_H
#define WARPEFFECT_H

#include <QObject>
#include <QMediaPlayer>
#include "gameplayitem.h"

class QMediaPlaylist;
class QTimer;

class WarpEffect : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit WarpEffect(QGraphicsItem *, QObject * = 0);
    ~WarpEffect();

    void stopTime() override;
    void startTime() override;

    int type() const override;

private slots:
    void slotNextFrame();
    void slotMediaStateChanged(QMediaPlayer::State);

private /*functions*/:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private /*objects*/:
    QMediaPlayer *player;
    QTimer *timer;
    QPixmap sprite_image;
    int current_frame {0};
    QGraphicsItem *warped_item;

    static unsigned short number_of_warps;
    bool _paused {false};
};

#endif // WARPEFFECT_H
