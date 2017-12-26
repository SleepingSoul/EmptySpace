#include "gameplaymovableitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>

bool GameplayMovableItem::collidesWithImpassableItem() const
{
    foreach (auto item, scene()->collidingItems(this)) {
        if (item->type() == UserType + 2)   /*(UserType + 2) --- impassable item type*/
            return true;
    }
    return false;
}

GameplayMovableItem *GameplayMovableItem::collidesWithDamagebleItem() const
{
    foreach (auto item, scene()->collidingItems(this)) {
        if (item->type() == UserType + 3 || item->type() == UserType + 4)
            /*(UserType + 3) --- damageble item type*/
            return dynamic_cast <GameplayMovableItem *>(item);
    }
    return nullptr;
}

bool GameplayMovableItem::isHeroType() const
{
    return this->type() == UserType + 4;    /*hero type (also damageble type)*/
}

bool GameplayMovableItem::isInView() const
{
    return scene()->views().front()->sceneRect().contains(this->pos());
}
