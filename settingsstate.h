#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "state.h"
#include <QSettings>

class SettingsScene;
class QVBoxLayout;
class QSlider;
class QGraphicsView;
class QLabel;
class QPushButton;
class QMediaPlayer;
class QTimer;
class QQuickWidget;
class QComboBox;

class SettingsState : public State
{
    Q_OBJECT
public:
    SettingsState(GameWindow *, const int, const int);
    ~SettingsState();
    QWidget *getStateWidget() const override;
    int Volume() const;

signals:
    void signalChangeVolume(int);
    void signalChangeWallpaper(int);

private /*objects*/:
    /*Settings:*/
    QSettings settings;

    GameWindow *game_window;
    QGridLayout *lout;
    QSlider *volume_slider;
    QComboBox *wp_combo_box;
    QPixmap *bg;
    SettingsScene *pstgs_scene;
    QGraphicsView *pgraphics_view;
    QTimer *timer_before_change;
    QLabel *lbl_volume;
    QPushButton *btn_to_menu;
    QPushButton *btn_apply_wp_change;
    QMediaPlayer *player;
    QWidget *state_widget;
    const int wwidth;
    const int wheight;

    unsigned short _last_background_index;

private /*functions*/:
    void readSettings();
    void writeSettings();

private slots:
    void slotChangeVolume(int);
    void slotBtnToMenuClicked();
    void slotMenuState();
    void slotWpChangeApplied(int);
};

#endif // SETTINGSSTATE_H
