#include "gameplaymovableitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>

bool GameplayMovableItem::collidesWithImpassableItem() const
{
    foreach (auto item, scene()->collidingItems(this)) {
        if (item->type() == ImpassableType)
            return true;
    }
    return false;
}

GameplayMovableItem *GameplayMovableItem::collidesWithDamagebleItem() const
{
    foreach (auto item, scene()->collidingItems(this)) {
        if (item->type() == DamagebleType || item->type() == HeroType)
            return dynamic_cast <GameplayMovableItem *>(item);
    }
    return nullptr;
}

GameplayItem *GameplayMovableItem::collidesWithBonusItem() const
{
    foreach (auto item, scene()->collidingItems(this)) {
        if (item->type() == HealingType)
            return dynamic_cast <GameplayItem *>(item);
    }
    return nullptr;
}

bool GameplayMovableItem::isHeroType() const
{
    return this->type() == HeroType;    /*hero type (also damageble type)*/
}

bool GameplayMovableItem::isInView() const
{
    return scene()->views().front()->sceneRect().contains(this->pos());
}
