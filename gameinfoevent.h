#ifndef GAMEINFOEVENT_H
#define GAMEINFOEVENT_H

#include "gameevent.h"
#include <QObject>

class InfoWindow;
class QPushButton;
class QGraphicsScene;
class QGraphicsProxyWidget;

class GameInfoEvent : public QObject, public GameEvent
{
    Q_OBJECT
public:
    explicit GameInfoEvent(QObject * = 0);
    ~GameInfoEvent();

    void setInfoWindow(InfoWindow *);

    void executeEvent(QGraphicsScene *) override;
    EventType getEventType() const override;

private:
    InfoWindow *info_window {nullptr};
    QPushButton *btn_ok;
    QGraphicsProxyWidget *proxy_btn_ok;
    QGraphicsScene *scene;

private slots:
    void slotBtnClicked();
};

#endif // GAMEINFOEVENT_H
