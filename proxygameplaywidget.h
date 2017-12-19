#ifndef PROXYGAMEPLAYWIDGET_H
#define PROXYGAMEPLAYWIDGET_H

#include <QGraphicsProxyWidget>
#include "gameplayitem.h"
#include <QDebug>

class ProxyGameplayWidget : public QGraphicsProxyWidget, public GameplayItem
{
public:
    enum {Type = UserType + 3};

    int type() const
    {
        return Type;
    }

    ProxyGameplayWidget();
    ~ProxyGameplayWidget();

    void stopTime() override {}
    void startTime() override {}
};

#endif // PROXYGAMEPLAYWIDGET_H
