#ifndef ABOUTSTATE_H
#define ABOUTSTATE_H

#include "state.h"

class GameWindow;
class AboutScene;
class QGraphicsView;
class QPushButton;
class QMediaPlayer;
class QTimer;
class QGridLayout;
class QLabel;

class AboutState : public State
{
    Q_OBJECT
public:
    AboutState(GameWindow *, const int, const int);
    ~AboutState();
    QWidget *getStateWidget() const override;

private:
    /*scene and view of this state*/
    AboutScene    *pabout_scene;
    QGraphicsView *pgraphics_view;

    /*GameWindow pointer to emin change state signal*/
    GameWindow    *game_window;

    /*Buttons*/
    QPushButton   *btn_menu;

    /*Player for any exactly this state's sounds or music*/
    QMediaPlayer  *player;

    /*Timers*/
    QTimer        *timer_before_change;

    /*State widget layout*/
    QGridLayout   *lout;

    /*State widget*/
    QWidget       *state_widget;

    QLabel        *lbl_text_about;

    /*Sizes*/
    const int     wwidth;
    const int     wheight;

private slots:
    void slotBtnMenuClicked();
    void slotMenuState();
};

#endif // ABOUTSTATE_H
