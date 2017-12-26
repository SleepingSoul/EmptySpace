#ifndef GAMEEVENTOFAPPEARING_H
#define GAMEEVENTOFAPPEARING_H

#include "gameevent.h"

class GameEventOfAppearing : public GameEvent
{
public:
    GameEventOfAppearing();
    ~GameEventOfAppearing();

    void executeEvent(QGraphicsScene *) override;
    EventType getEventType() const override;
    void setAppearingItem(QGraphicsItem *);

private:
    QGraphicsItem *item;
};

#endif // GAMEEVENTOFAPPEARING_H
