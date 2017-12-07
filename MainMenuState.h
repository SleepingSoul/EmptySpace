#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"

class QPushButton;
class QVBoxLayout;
class QPixmap;
class QGraphicsView;
class QMediaPlayer;
class QTimer;
class QWidget;
class MenuScene;

class MainMenuState : public State
{
    Q_OBJECT
public:
    MainMenuState(GameWindow *, const int ww, const int wh);
    ~MainMenuState();
    QWidget *getStateWidget() const override;

private:
    QGridLayout          *lout;
    MenuScene            *pmenu_scene;
    QGraphicsView        *pgraphics_view;
    GameWindow           *game_window;
    QMediaPlayer         *player;
    QPushButton          *btn_play;
    QPushButton          *btn_settings;
    QPushButton          *btn_about;
    QPushButton          *btn_quit;
    QTimer               *timer_before_change;
    QWidget              *state_widget;
    const int            wwidth;
    const int            wheight;
    void                 (*func_ptr)();

private slots:
    void slotButtonPlay();
    void slotGameplayState();
    void slotSettingsState();
    void slotButtonSettings();
    void slotButtonQuit();
    void slotQuitFromApp();
};

#endif // MAINMENUSTATE_H
