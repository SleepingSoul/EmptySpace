#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <QVBoxLayout>
#include <QSlider>
#include <QGraphicsView>
#include "state.h"
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>

class SettingsScene;

class SettingsState : public State
{
    Q_OBJECT
public:
    SettingsState(GameWindow *, const int, const int, const int);
    ~SettingsState();
    QWidget *getStateWidget() const override;

signals:
    void signalChangeVolume(int);

private:
    GameWindow *game_window;
    QGridLayout *lout;
    QSlider *volume_slider;
    QPixmap *bg;
    SettingsScene *pstgs_scene;
    QGraphicsView *pgraphics_view;
    QTimer *timer_before_change;
    QLabel *lbl_volume;
    QPushButton *btn_to_menu;
    QMediaPlayer *player;
    QWidget *state_widget;
    const int wwidth;
    const int wheight;

private slots:
    void slotChangeVolume(int);
    void slotBtnToMenuClicked();
    void slotMenuState();
};

#endif // SETTINGSSTATE_H
