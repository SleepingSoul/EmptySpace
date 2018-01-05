#include <QBitmap>
#include <QRegion>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>
#include <QWidget>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include "menuscene.h"
#include "mainmenustate.h"
#include "gamewindow.h"
#include "gameplaystate.h"
#include "sizes.h"
#include "templates.h"
#include "sounds.h"
#include <QDateTime>
#include <QLabel>
#include <QGraphicsSimpleTextItem>
#include "customtextitem.h"

MainMenuState::MainMenuState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd),
      settings(QApplication::organizationName(), QApplication::applicationName())
{
    /*Allocate memory and set up of menu scene*/
    pmenu_scene = new MenuScene                 (wwidth, wheight);
    pmenu_scene->setSceneRect                   (0, 0, wwidth, wheight);

    readSettings();

    /*Allocate memory and set up for graphics view widget, which will
     * contain out scene and will be built into our main "GameWidget"*/
    pgraphics_view = new QGraphicsView;
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene                    (pmenu_scene);

    /*Set up music*/
    player = new QMediaPlayer;
    player->setVolume(50);

    /*Allocate memory for buttons*/
    btn_play = new QPushButton;
    btn_settings = new QPushButton;
    btn_about = new QPushButton;
    btn_quit = new QPushButton;
    btn_new_game = new QPushButton;

    /*Set up buttons*/
    setUpButton(btn_play, "btnPlay.png");
    setUpButton(btn_settings, "btnSettings.png");
    setUpButton(btn_about, "btnAbout.png");
    setUpButton(btn_quit, "btnQuit.png");
    setUpButton(btn_new_game, "btnNewGame.png");

    /*Make buttons proxy to built them into scene*/
    QGraphicsProxyWidget *proxy_play = pmenu_scene->addWidget    (btn_play);
    QGraphicsProxyWidget *proxy_settings = pmenu_scene->addWidget(btn_settings);
    QGraphicsProxyWidget *proxy_about  = pmenu_scene->addWidget  (btn_about);
    QGraphicsProxyWidget *proxy_quit = pmenu_scene->addWidget    (btn_quit);
    QGraphicsProxyWidget *proxy_new_game = pmenu_scene->addWidget(btn_new_game);

    /*Time*/
    text_time = new CustomTextItem;
    pmenu_scene->addItem(text_time);
    text_time->setPos(wwidth - 200, 100);

    /*Set up position of buttons on the scene*/
    proxy_play->setPos    (100, 200);
    proxy_new_game->setPos(proxy_play->pos() + QPoint(0, 75));
    proxy_settings->setPos(proxy_new_game->pos() + QPoint(0, 75));
    proxy_about->setPos   (proxy_settings->pos() + QPoint(0, 75));
    proxy_quit->setPos    (proxy_about->pos() + QPoint(0, 75));

    /*Connect buttons signals->this class slots to handle it*/
    connect(btn_play,     SIGNAL(clicked(bool)), SLOT(slotButtonPlay()));
    connect(btn_settings, SIGNAL(clicked(bool)), SLOT(slotButtonSettings()));
    connect(btn_quit,     SIGNAL(clicked(bool)), SLOT(slotButtonQuit()));
    connect(btn_about,    SIGNAL(clicked(bool)), SLOT(slotButtonAbout()));
    connect(btn_new_game, SIGNAL(clicked(bool)), SLOT(slotButtonNewGame()));

    /*Allocate and set up layout*/
    lout = new QGridLayout;
    lout->addWidget(pgraphics_view);
    lout->setContentsMargins(0, 0, 0, 0);

    /*Allocate memory for timer, which will make a little pause after
     * button click till widget changes*/
    timer_before_change = new QTimer(this);
    timer_current_time = new QTimer(this);
    connect(timer_current_time, SIGNAL(timeout()), SLOT(slotUpdateTime()));
    timer_current_time->start(30);

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout(lout);
}

MainMenuState::~MainMenuState()
{
    /*Here we should carefully delete all dynamic memory we had allocated*/
    delete player;
    delete lout;
    delete btn_play;
    delete btn_settings;
    delete btn_about;
    delete btn_quit;
    delete timer_before_change;
    delete pgraphics_view;
    delete pmenu_scene;
}

QWidget *MainMenuState::getStateWidget() const
{
    return state_widget;
}

void MainMenuState::slotButtonPlay()
{
    /*If user clicked button "Play",
     * we stop the music,
     * enable click sound, w8
     * little amount of time and
     * than emit signal to change the
     * state of widget*/
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    /*We connect this timer to slot depends on required next state*/
    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotGameplayState()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotGameplayState()
{
    qDebug() << "Set gameplay state from MainMenuState called.";
    /*Just stop timer and change state*/
    timer_before_change->stop();
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotGameplayState()));
    player->stop();
    game_window->setState(State::Gameplay);
}

void MainMenuState::slotButtonSettings()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotSettingsState()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotSettingsState()
{
    timer_before_change->stop();
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotSettingsState()));
    player->stop();
    game_window->setState(State::Settings);
}

void MainMenuState::slotAboutState()
{
    timer_before_change->stop();
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotAboutState()));
    player->stop();

    game_window->setState(State::About);
}

void MainMenuState::slotButtonQuit()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotQuitFromApp()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotButtonAbout()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotAboutState()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotButtonNewGame()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotNewGame()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotNewGame()
{
    timer_before_change->stop();
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotNewGame()));
    player->stop();

    game_window->setState(State::NewGameplay);
}

void MainMenuState::slotQuitFromApp()
{
    QApplication::quit();
}

void MainMenuState::slotChangeWallpaper(int idx)
{
    pmenu_scene->setBackgroundImage(idx);
}

void MainMenuState::readSettings()
{
    settings.beginGroup("/Settings");
    int bg_index(settings.value("/bg_index", 0).toInt());
    settings.endGroup();

    pmenu_scene->setBackgroundImage(bg_index);
}

void MainMenuState::slotUpdateTime()
{
    pmenu_scene->update();
}
