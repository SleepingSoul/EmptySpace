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

class AboutState : public State
{
    Q_OBJECT
public:
    AboutState(const int, const int);
    ~AboutState();
    QWidget *getStateWidget() const override;

private:
    AboutScene    *pabout_scene;
    QGraphicsView *pgraphics_view;
    GameWindow    *game_window;
    QPushButton   *btn_menu;
    QMediaPlayer  *player;
    QTimer        *timer_before_change;
    QGridLayout   *lout;
    const int     wwidth;
    const int     wheight;

private slots:
    void slotBtnMenuClicked();
    void slotMenuState();
};

#endif // ABOUTSTATE_H
