 #include "gamewindow.h"
#include "mainmenustate.h"
#include "gameplaystate.h"
#include "settingsstate.h"
#include "sizes.h"
#include "aboutstate.h"
#include <QPaintEngine>
#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "gamescene.h"
#include "hero.h"
#include "bgmusicplayer.h"

GameWindow::GameWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    QRect rect = QApplication::desktop()->screenGeometry();
    wwidth = rect.width();
    wheight = rect.height();

    music_player = new BGMusicPlayer;

    menu_state =     new MainMenuState(this, wwidth, wheight);
    settings_state = new SettingsState(this, wwidth, wheight, 100); /*from qsettings*/
    gameplay_state = new GameplayState(this, wwidth, wheight);

    connect(dynamic_cast <SettingsState *>(settings_state), SIGNAL(signalChangeVolume(int)),
            music_player,                                   SLOT(setVolume(int)));
    this->setWindowIcon(QIcon(QPixmap("es_icon.png")));

    this->addWidget(menu_state->getStateWidget());
    this->addWidget(settings_state->getStateWidget());
    this->addWidget(gameplay_state->getStateWidget());

    this->setState(State::MainMenu);
}

GameWindow::~GameWindow()
{
    delete music_player;
}

void GameWindow::setState(State::ID id)
{
    switch (id) {
    case State::MainMenu:
        music_player->playMenuMusic();
        this->setCurrentIndex(State::MainMenu);
        break;

    case State::Gameplay:
        music_player->playGameplayMusic();
        this->setCurrentIndex(State::Gameplay);
        qobject_cast <GameplayState *>(gameplay_state)->getScene()->setFocus();
        qDebug() << qobject_cast <GameplayState *>(gameplay_state)->getScene()->hasFocus();
        break;

    case State::Settings:
        this->setCurrentIndex(State::Settings);
        break;

    case State::About:
        music_player->playMenuMusic();
        this->setCurrentIndex(State::About);
    }
}
