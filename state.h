#ifndef STATE_H
#define STATE_H

#include <QObject>
class GameWindow;

class State : public QObject
{
    Q_OBJECT
public:
    enum ID{MainMenu = 0, Gameplay, Settings};

    State() {}
    virtual ~State() {}
    virtual void buildWindowState(GameWindow *) = 0;
};

#endif // STATE_H
