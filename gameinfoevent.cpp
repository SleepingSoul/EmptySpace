#include "gameinfoevent.h"
#include "quitwindow.h"
#include "infowindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "templates.h"

GameInfoEvent::GameInfoEvent(QObject *parent)
    : QObject(parent)
{
    btn_ok = new QPushButton();
    setUpButton(btn_ok, "btn_got_it.png");
    connect(btn_ok, SIGNAL(clicked(bool)), SLOT(slotBtnClicked()));
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
    GameInfoEvent::scene = scene;
    auto rect = scene->views().front()->sceneRect();
    info_window->setPos(rect.topRight() + QPointF(-info_window->Width() - 50, 50));

    info_window->setZValue(3);

    scene->addItem(info_window);
    proxy_btn_ok = scene->addWidget(btn_ok);
    proxy_btn_ok->setZValue(3);
    proxy_btn_ok->setPos(rect.topRight() + QPointF(-info_window->Width() + 20, info_window->Height() - 30));
}

void GameInfoEvent::slotBtnClicked()
{
    scene->removeItem(proxy_btn_ok);
    scene->removeItem(info_window);
}

GameInfoEvent::EventType GameInfoEvent::getEventType() const
{
    return InfoEvent;
}
