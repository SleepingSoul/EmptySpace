#ifndef GAMEPLAYITEM_H
#define GAMEPLAYITEM_H

/*This is interface of item, that is managed to have
 * timer and it is on the graphics scene on the moment of pausing. It
 * is required to have oportunity to stop all
 * timers, whene pause is enabled.*/

class GameplayItem
{
public:
    virtual void  stopTime() = 0;
    virtual void startTime() = 0;
};

#endif // GAMEPLAYITEM_H
