#ifndef GAMEEVENT_H
#define GAMEEVENT_H

class QGraphicsScene;
class QPoint;
#include <QGraphicsView>

/*This class is an interface of any game event.
 * Game event is some event which has to be executed
 * in runtime of gameplay process. For example,
 * appearing of enemy on the map when hero is close enough.
 * */

class GameEvent
{
public:
    enum EventType{InfoEvent = 0, EventOfAppearing};

    GameEvent() {}
    virtual ~GameEvent() = 0;

    virtual void executeEvent(QGraphicsScene *) = 0;
    virtual EventType getEventType() const = 0;

    bool cause(QGraphicsView *view) const
    {
        return view->sceneRect().contains(cause_point);
    }
    bool executed() const
    {
        return event_executed;
    }
    void setCausePoint(const QPoint p)
    {
        cause_point = p;
    }


protected:
    QPoint cause_point;
    bool event_executed {false};
};

#endif // GAMEEVENT_H
