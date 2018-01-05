#include "gameinfoevent.h"
#include "quitwindow.h"
#include "infowindow.h"
#include "gamescene.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "templates.h"

GameInfoEvent::GameInfoEvent()
{

}

GameInfoEvent::~GameInfoEvent()
{

}

void GameInfoEvent::setInfoWindow(InfoWindow *iw)
{
    info_window = iw;
}

void GameInfoEvent::executeEvent(QGraphicsScene *scene)
{
    event_executed = true;
    auto rect = scene->views().front()->sceneRect();
    info_window->setPos(rect.topRight() + QPointF(-info_window->Width() - 50, 50));

    info_window->setZValue(3);

    dynamic_cast <GameScene *>(scene)->addInfoWindow(info_window);
}

GameInfoEvent::EventType GameInfoEvent::getEventType() const
{
    return InfoEvent;
}
