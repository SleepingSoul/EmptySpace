#include "gamewindow.h"
#include "MainMenuState.h"
#include "gameplaystate.h"
#include "settingsstate.h"
#include <QPaintEngine>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent)
{
    state = nullptr;
    //state_allocated_earlier = new GameplayState(this);      //pre-allocation (3-4 sec)
    music_player = new BGMusicPlayer;
    setState(State::MainMenu);
}

GameWindow::~GameWindow()
{
    delete music_player;
}

void GameWindow::setState(State::ID id)
{
    switch (id) {
    case State::MainMenu:
        if (state != nullptr) delete state;
        state = new MainMenuState();
        state->buildWindowState(this);
        music_player->playMenuMusic();
        break;
    case State::Gameplay:
        if (state != nullptr) delete state;
        state = new GameplayState(this);
        state->buildWindowState(this);
        music_player->playGameplayMusic();
        break;
    case State::Settings:
        if (state != nullptr) delete state;
        state = new SettingsState(music_player->volume());
        connect(dynamic_cast <SettingsState *>(state), SIGNAL(signalChangeVolume(int)),
                music_player,                          SLOT  (setVolume(int)));
        state->buildWindowState(this);
        music_player->playingMenuMusic();
        break;
    }
}
