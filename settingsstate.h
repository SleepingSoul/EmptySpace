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
    SettingsState(const int);
    ~SettingsState();
    void buildWindowState(GameWindow *) override;

signals:
    void signalChangeVolume(int);

private:
    GameWindow *gwd;
    QVBoxLayout *lout;
    QSlider *volume_slider;
    QPixmap *bg;
    SettingsScene *pstgs_scene;
    QGraphicsView *pgraphics_view;
    QTimer *timer_before_change;
    QLabel *lbl_volume;
    QPushButton *btn_to_menu;
    QMediaPlayer *player;

private slots:
    void slotChangeVolume(int);
    void slotBtnToMenuClicked();
    void slotMenuState();
};

#endif // SETTINGSSTATE_H
