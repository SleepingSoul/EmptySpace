#ifndef GAMEPLAYMOVABLEITEM_H
#define GAMEPLAYMOVABLEITEM_H

#include "gameplayitem.h"

class GameplayMovableItem : public GameplayItem
{
public:
    virtual void getDamage(const int) = 0;
    void  stopTime() override  = 0;
    void startTime() override = 0;
    bool collidesWithImpassableItem() const;
    GameplayMovableItem *collidesWithDamagebleItem() const;
    bool isHeroType() const;
    bool isInView() const;
};

#endif // GAMEPLAYMOVABLEITEM_H
