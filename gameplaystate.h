#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "state.h"

class QuitWindow;
class GameScene;
class QGraphicsView;
class Hero;
class State;
class QPushButton;
class QVBoxLayout;
class QMediaPlayer;
class QTimer;
class QGraphicsProxyWidget;
class QGraphicsScene;
class GameView;
class QDateTime;
class QLabel;

class GameplayState : public State
{
    Q_OBJECT
public:
    GameplayState(GameWindow *, const int, const int);
    ~GameplayState();
    QWidget *getStateWidget() const override;
    QGraphicsView *getView() const;

private /*objects*/:
    /*Main view elements: Scene, View and it's layout*/
    GameScene            *pgraphics_scene;
    GameView             *pgraphics_view;
    QVBoxLayout          *lout;
    Hero                 *phero;

    /*We store Game Window ptr to change it's state when required*/
    GameWindow           *game_window;

    /*Buttons*/
    QPushButton          *btn_to_menu;
    QPushButton          *btn_pause;
    QGraphicsProxyWidget *proxy_btn_ok;
    QGraphicsProxyWidget *proxy_btn_no;

    /*Music features*/
    QMediaPlayer         *player;               /*Media player for buttin clicked sound*/
    QTimer               *timer_before_change;  /*Timer after some button has clicked*/
    QTimer               *cursor_timer;
    QTimer               *change_time_timer;

    /*Graphics*/
    QPixmap              *quit_pic;
    QuitWindow           *quit_window;

    /*Time*/
    QLabel               *lbl_time;

    /*Main state widget*/
    QWidget              *state_widget;

    /*Widget size constants*/
    const int            wwidth;
    const int            wheight;

    /*Pause flag*/
    bool paused {false};

private /*functions*/:
    void quitHandler();
    //void setUpButton(QPushButton *, const char *);

private slots:
    void slotButtonToMenuClicked();
    void slotMenuState();
    void slotQuitConfirmed();
    void slotDontQuit();
    void slotButtonPauseClicked();
    void slotUpdateTime();
};

#endif // GAMEPLAYSTATE_H
