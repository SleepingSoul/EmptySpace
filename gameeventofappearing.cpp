#include "gameeventofappearing.h"

GameEventOfAppearing::GameEventOfAppearing()
{

}

GameEventOfAppearing::~GameEventOfAppearing()
{

}

void GameEventOfAppearing::executeEvent(QGraphicsScene *scene)
{
    event_executed = true;
    scene->addItem(item);
}

GameEventOfAppearing::EventType GameEventOfAppearing::getEventType() const
{
    return EventOfAppearing;
}

void GameEventOfAppearing::setAppearingItem(QGraphicsItem *ai)
{
    item = ai;
}
