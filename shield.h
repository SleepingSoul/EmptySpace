#ifndef SHIELD_H
#define SHIELD_H

#include "gameplaymovableitem.h"
#include <QObject>

class QTimer;

class Shield : public QObject, public GameplayMovableItem
{
    Q_OBJECT
public:
    explicit Shield(QObject *parent = 0);
    ~Shield();

    void getDamage(const int) override;
    void startTime() override;
    void stopTime() override;
    int type() const override;

    void activate();

signals:
    void signalShieldExpired();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap shield_image;
    QTimer *timer;
    bool _timer_was_stoped {false};
    int hp {500};

private slots:
    void slotTimer();
};

#endif // SHIELD_H
