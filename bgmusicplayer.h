#ifndef BGMUSICPLAYER_H
#define BGMUSICPLAYER_H

#include <QMediaPlayer>
#include <QObject>

class BGMusicPlayer : public QObject
{
    Q_OBJECT
public:
    BGMusicPlayer();
    ~BGMusicPlayer();

    void playMenuMusic();
    void playGameplayMusic();

    bool playingMenuMusic() const;
    bool playingGameplayMusic() const;
    int volume() const;

public slots:
    void setVolume(int);

private:
    QMediaPlayer *player;
    QMediaContent *menu_music;
    QMediaContent *gameplay_music;

    bool is_playing_menu_music {false};
    bool is_playing_gameplay_music {false};
};

#endif // BGMUSICPLAYER_H
