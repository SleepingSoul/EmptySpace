#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QStackedWidget>
#include "state.h"
#include "global_enumerations.h"

class QGraphicsView;
class QWidget;
class QLabel;
class QGridLayout;
class CustomScene;
class QVBoxLayout;
class BGMusicPlayer;
class GameplayState;
class SettingsState;
class MediaCache;

class GameWindow : public QStackedWidget
{
    Q_OBJECT
public:
    GameWindow();
    ~GameWindow();
    void setState(State::ID);
    QCursor getStandardCursor() const;
    QPixmap *getPictureFromCache(Pictures::Type);

private:
    /*Widnow states*/
    State           *menu_state;
    State           *settings_state;
    State           *gameplay_state;
    State           *about_state;

    QCursor standard_cursor;

    BGMusicPlayer   *music_player;
    MediaCache      *m_cache;
    int             wwidth;
    int             wheight;
};

#endif // GAMEWINDOW_H
