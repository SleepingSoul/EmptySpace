#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "customscene.h"
#include "hero.h"
#include "bgmusicplayer.h"

#include "state.h"

class GameplayState;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void setState(State::ID);

private:
    CustomScene *  pgraphics_scene;
    QGraphicsView *pgraphics_view;
    Hero *         phero;
    State *        state;

    GameplayState *state_allocated_earlier;

    BGMusicPlayer *music_player;

};

#endif // GAMEWINDOW_H
