#ifndef GAMEINFOEVENT_H
#define GAMEINFOEVENT_H

#include "gameevent.h"
#include <QObject>

class InfoWindow;
class QPushButton;
class QGraphicsScene;
class QGraphicsProxyWidget;

class GameInfoEvent : public GameEvent
{
public:
    GameInfoEvent();
    ~GameInfoEvent();

    void setInfoWindow(InfoWindow *);

    void executeEvent(QGraphicsScene *) override;
    EventType getEventType() const override;

private:
    InfoWindow *info_window {nullptr};
};

#endif // GAMEINFOEVENT_H
