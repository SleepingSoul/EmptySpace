#include "bgmusicplayer.h"

BGMusicPlayer::BGMusicPlayer()
{
    player = new QMediaPlayer;
    gameplay_music = new QMediaContent(QUrl::fromLocalFile("Public Enemy.mp3"));
    menu_music = new QMediaContent(QUrl::fromLocalFile("Wings of Liberty.mp3"));
}

BGMusicPlayer::~BGMusicPlayer()
{
    delete player;
    delete gameplay_music;
    delete menu_music;
}

void BGMusicPlayer::playGameplayMusic()
{
    if (is_playing_gameplay_music)
        return;

    is_playing_gameplay_music = true;
    is_playing_menu_music = false;

    if (player->state() == QMediaPlayer::PlayingState)
        player->stop();
    player->setMedia(*gameplay_music);
    player->play();
}

void BGMusicPlayer::playMenuMusic()
{
    if (is_playing_menu_music)
        return;

    is_playing_menu_music = true;
    is_playing_gameplay_music = false;

    if (player->state() == QMediaPlayer::PlayingState)
        player->stop();
    player->setMedia(*menu_music);
    player->play();
}

void BGMusicPlayer::setVolume(int v)
{
    player->setVolume(v);
}

bool BGMusicPlayer::playingGameplayMusic() const
{
    return is_playing_gameplay_music;
}

bool BGMusicPlayer::playingMenuMusic() const
{
    return is_playing_menu_music;
}

int BGMusicPlayer::volume() const
{
    return player->volume();
}
