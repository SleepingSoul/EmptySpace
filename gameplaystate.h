#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "customscene.h"
#include "QGraphicsView"
#include "hero.h"
#include "state.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
class GameWindow;
class QuitWindow;

class GameplayState : public State
{
    Q_OBJECT
public:
    GameplayState(GameWindow *);
    ~GameplayState();
    void buildWindowState(GameWindow *) override;

private /*objects*/:
    CustomScene *  pgraphics_scene;
    QGraphicsView *pgraphics_view;
    Hero *         phero;
    GameWindow *_gw;
    QVBoxLayout *lout;
    QPushButton *btn_to_menu;
    QMediaPlayer *player;
    QTimer *timer_before_change;
    QPixmap *quit_pic;
    QPushButton *btn_quit;
    QPushButton *btn_dont_quit;
    QuitWindow *quit_window;
    QGraphicsProxyWidget *proxy_btn_ok;
    QGraphicsProxyWidget *proxy_btn_no;

private /*functions*/:
    void quitHandler();

private slots:
    void slotButtonToMenuClicked();
    void slotMenuState();
    void slotQuitConfirmed();
    void slotDontQuit();
};

#endif // GAMEPLAYSTATE_H
