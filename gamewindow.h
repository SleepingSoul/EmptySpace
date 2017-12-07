#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QStackedWidget>
#include "state.h"

class QGraphicsView;
class QWidget;
class QLabel;
class QGridLayout;
class CustomScene;
class QVBoxLayout;
class BGMusicPlayer;
class GameplayState;
class SettingsState;

class GameWindow : public QStackedWidget
{
    Q_OBJECT
public:
    GameWindow();
    ~GameWindow();
    void setState(State::ID);

private:
    /*Widnow states*/
    State           *menu_state;
    State           *settings_state;
    State           *gameplay_state;
    State           *about_state;

    /*Main view elements: Scene, View and it's layout*/
//    CustomScene     *pgraphics_scene;
//    QGraphicsView   *pgraphics_view;
//    QVBoxLayout     *main_layout;
    BGMusicPlayer   *music_player;
    int             wwidth;
    int             wheight;
};

#endif // GAMEWINDOW_H
