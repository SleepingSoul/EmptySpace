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
#include <QIcon>

GameWindow::GameWindow()
{
    /*Set up program window attributes*/
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    QRect rect = QApplication::desktop()->screenGeometry();
    wwidth = rect.width();
    wheight = rect.height();

    /*Main bg music player allocation*/
    music_player = new BGMusicPlayer;

    standard_cursor = QCursor(QPixmap("menu_cursor.png"));

    /*All states memory allocation*/
    menu_state =     new MainMenuState(this, wwidth, wheight);
    settings_state = new SettingsState(this, wwidth, wheight); /*from qsettings*/
    gameplay_state = new GameplayState(this, wwidth, wheight);
    about_state =    new AboutState   (this, wwidth, wheight);

    /*In settings state user has oportunity to control some params of program, so
     * there is aditional connections*/
    connect(dynamic_cast <SettingsState *>(settings_state), SIGNAL(signalChangeVolume(int)),
            music_player,                                   SLOT(setVolume(int)));
    connect(dynamic_cast <SettingsState *>(settings_state), SIGNAL(signalChangeWallpaper(int)),
            dynamic_cast <MainMenuState *>(menu_state),     SLOT(slotChangeWallpaper(int)));

    /*Now, we will set correct volume to music player*/
    music_player->setVolume(dynamic_cast <SettingsState *>(settings_state)->Volume());

    this->setWindowIcon(QIcon(QPixmap("es_icon.png")));

    /*We add all state's widgets in stacked widget*/
    this->addWidget(menu_state->getStateWidget());
    this->addWidget(settings_state->getStateWidget());
    this->addWidget(gameplay_state->getStateWidget());
    this->addWidget(about_state->getStateWidget());

    this->setState(State::MainMenu);
    QApplication::setOverrideCursor(this->getStandardCursor());
}

GameWindow::~GameWindow()
{
    delete gameplay_state;
    delete menu_state;
    delete settings_state;
    delete about_state;
    delete music_player;
}

QCursor GameWindow::getStandardCursor() const
{
    return standard_cursor;
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
        dynamic_cast <GameplayState *>(gameplay_state)->getView()->setFocus();
        break;

    case State::Settings:
        this->setCurrentIndex(State::Settings);
        break;

    case State::About:
        music_player->playMenuMusic();
        this->setCurrentIndex(State::About);
        break;
    }
}
