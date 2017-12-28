#ifndef CHARGER_H
#define CHARGER_H

#include "gameplayitem.h"
#include <QObject>

class QTimer;

class Charger : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    enum ChargerState {ChargerIsAvailable = 0, ChargerUnavailable};
    explicit Charger(QObject * = 0);
    ~Charger();

    void stopTime() override;
    void startTime() override;
    int type() const override;
    void setState(const ChargerState);

signals:
    void signalCharged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QTimer *timer;
    QPixmap bg_image_a;
    QPixmap bg_image_una;
    ChargerState state {ChargerIsAvailable};
    bool _timer_was_stoped {false};
    int progress {0};

private slots:
    void slotTimer();
    void slotHeroCharged();
};

#endif // CHARGER_H
