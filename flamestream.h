#ifndef FLAMESTREAM_H
#define FLAMESTREAM_H

#include <QGraphicsItem>
#include <QObject>
#include "gameplayitem.h"

class QTimer;

class FlameStream : public QObject, public QGraphicsItem, public GameplayItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum {Type = UserType + 1};

    explicit FlameStream(QObject *parent = 0);
    ~FlameStream();

    int type() const
    {
        return Type;
    }

    void stopTime() override {}
    void startTime() override {}
    void shootCall(const bool);

private /*objects*/:
    QPixmap *sprite;
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
