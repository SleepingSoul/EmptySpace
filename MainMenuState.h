#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include "menuscene.h"

class MainMenuState : public State
{
    Q_OBJECT
public:
    MainMenuState();
    ~MainMenuState();
    void buildWindowState(GameWindow *) override;

private:
    QVBoxLayout          *lout;
    MenuScene            *pmenu_scene;
    QGraphicsView        *pgraphics_view;
    GameWindow           *gwd;
    QMediaPlayer         *player;
    QPushButton          *btnPlay;
    QPushButton          *btnSettings;
    QGraphicsProxyWidget *proxyPlay;
    QGraphicsProxyWidget *proxySettings;
    QTimer               *timerBeforeChange;

private slots:
    void slotButtonPlay();
    void slotGameplayState();
    void slotSettingsState();
    void slotButtonSettings();
    //void slotSettingsState(QMediaPlayer::MediaStatus);
};

#endif // MAINMENUSTATE_H
