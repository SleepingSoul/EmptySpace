#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QPixmap>
#include <QCursor>

class GameWindow;
class QGridLayout;
class QGraphicsView;

class State : public QObject
{
    Q_OBJECT
public:
    enum ID{MainMenu = 0, Settings, Gameplay, About, NewGameplay};

    State() {}
    virtual ~State() {}
    virtual QWidget *getStateWidget() const = 0;
};

#endif // STATE_H
