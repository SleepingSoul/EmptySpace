#ifndef HEROTHRUST_H
#define HEROTHRUST_H

#include <QObject>
#include <QGraphicsItem>
#include "gameplayitem.h"

class QTimer;
class QPixmap;

class HeroThrust : public QObject, public GameplayItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit HeroThrust(QObject *parent = 0);
    ~HeroThrust();

    void stopTime() override;
    void startTime() override;
    void setMoving(const bool);

private /*functions*/:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPainterPath shape() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private /*objects*/:
    QPixmap *sprite;
    int     offset {30};
    QTimer  *timer;
    bool movingNow {false};

    /*objects required for thrusts changing realization*/
    unsigned short _flag_1 {0};
    unsigned short _flag_2 {0};
    unsigned short _counter{0};
    bool _direction;

private slots:
    void slotTick();
};

#endif // HEROTHRUST_H
