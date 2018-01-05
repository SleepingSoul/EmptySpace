#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"
#include <QSettings>

class QPushButton;
class QVBoxLayout;
class QPixmap;
class QGraphicsView;
class QMediaPlayer;
class QTimer;
class QWidget;
class MenuScene;
class QGraphicsSimpleTextItem;
class QLabel;
class CustomTextItem;

class MainMenuState : public State
{
    Q_OBJECT
public:
    MainMenuState(GameWindow *, const int ww, const int wh);
    ~MainMenuState();
    QWidget *getStateWidget() const override;

public slots:
    void slotChangeWallpaper(int);

private /*objects*/:
    QSettings settings;

    QGridLayout          *lout;
    MenuScene            *pmenu_scene;
    QGraphicsView        *pgraphics_view;
    GameWindow           *game_window;
    QMediaPlayer         *player;
    /*Buttons:*/
    QPushButton          *btn_play;
    QPushButton          *btn_settings;
    QPushButton          *btn_about;
    QPushButton          *btn_quit;
    QPushButton          *btn_new_game;

    QTimer               *timer_before_change;
    QTimer               *timer_current_time;
    QWidget              *state_widget;
    CustomTextItem *text_time;
    const int            wwidth;
    const int            wheight;

private /*functions*/:
    void readSettings();

private slots:
    void slotButtonPlay();
    void slotGameplayState();
    void slotSettingsState();
    void slotButtonSettings();
    void slotButtonQuit();
    void slotButtonAbout();
    void slotButtonNewGame();
    void slotAboutState();
    void slotNewGame();

    void slotUpdateTime();

    void slotQuitFromApp();
};

#endif // MAINMENUSTATE_H
