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
#include <QGraphicsProxyWidget>
#include "menuscene.h"
#include "mainmenustate.h"
#include "gamewindow.h"
#include "gameplaystate.h"
#include "sizes.h"

#define SELECT_SOUND "select_btn_sound.mp3"
#define CHANGE_T_MS 400

MainMenuState::MainMenuState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd)
{
    /*Allocate memory and set up of menu scene*/
    pmenu_scene = new MenuScene                 (wwidth, wheight);
    pmenu_scene->setSceneRect                   (0, 0, wwidth, wheight);

    /*Allocate memory and set up for graphics view widget, which will
     * contain out scene and will be built into our main "GameWidget"*/
    pgraphics_view = new QGraphicsView;
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene                    (pmenu_scene);

    /*Set up music*/
    player = new QMediaPlayer;

    /*Allocate memory for buttons*/
    btn_play = new QPushButton;
    btn_settings = new QPushButton;
    btn_about = new QPushButton;
    btn_quit = new QPushButton;

    /*Set up buttons design*/
    btn_play->setIcon         (QIcon(QPixmap("btnPlay.png")));
    btn_settings->setIcon     (QIcon(QPixmap("btnSettings.png")));
    btn_about->setIcon        (QIcon(QPixmap("btnAbout.png")));
    btn_quit->setIcon         (QIcon(QPixmap("btnQuit.png")));

    btn_play->setIconSize     (QSize(240, 52.12));
    btn_settings->setIconSize (QSize(240, 52.12));
    btn_about->setIconSize    (QSize(240, 52.12));
    btn_quit->setIconSize     (QSize(240, 52.12));

    /*This is shape for my custom button*/
    QRegion reg(QPolygon() << QPoint(0,10) << QPoint(10, 0) << QPoint(240, 0) << QPoint(240, 42.12) <<
                QPoint(230, 52.12) << QPoint(0, 52.12));

    btn_play->setMask    (reg);
    btn_settings->setMask(reg);
    btn_about->setMask   (reg);
    btn_quit->setMask    (reg);

    btn_play->setFixedSize    (240, 52.12);
    btn_settings->setFixedSize(240, 52.12);
    btn_about->setFixedSize   (240, 52.12);
    btn_quit->setFixedSize    (240, 52.12);

    /*Make buttons proxy to built them into scene*/
    QGraphicsProxyWidget *proxy_play = pmenu_scene->addWidget    (btn_play);
    QGraphicsProxyWidget *proxy_settings = pmenu_scene->addWidget(btn_settings);
    QGraphicsProxyWidget *proxy_about  = pmenu_scene->addWidget  (btn_about);
    QGraphicsProxyWidget *proxy_quit = pmenu_scene->addWidget    (btn_quit);

    /*Set up position of buttons on the scene*/
    proxy_play->setPos    (100, 200);
    proxy_settings->setPos(proxy_play->pos() + QPoint(0, 75));
    proxy_about->setPos   (proxy_settings->pos() + QPoint(0, 75));
    proxy_quit->setPos    (proxy_about->pos() + QPoint(0, 75));

    /*Connect buttons signals->this class slots to handle it*/
    connect(btn_play,     SIGNAL(clicked(bool)), SLOT(slotButtonPlay()));
    connect(btn_settings, SIGNAL(clicked(bool)), SLOT(slotButtonSettings()));
    connect(btn_quit,     SIGNAL(clicked(bool)), SLOT(slotButtonQuit()));

    /*Allocate and set up layout*/
    lout = new QGridLayout;
    lout->addWidget(pgraphics_view);
    lout->setContentsMargins(0, 0, 0, 0);

    /*Allocate memory for timer, which will make a little pause after
     * button click till widget changes*/
    timer_before_change = new QTimer;

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout(lout);

    QCursor cursor(QPixmap("menu_cursor.png"));
    state_widget->setCursor(cursor);
    btn_play->setCursor(cursor);
    btn_settings->setCursor(cursor);
    btn_about->setCursor(cursor);
    btn_quit->setCursor(cursor);
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
    qDebug() << "Scene objects: " << pmenu_scene->items().size() << " " << pmenu_scene->children().front();
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

void MainMenuState::slotButtonQuit()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotQuitFromApp()));
    timer_before_change->start(CHANGE_T_MS);
}

void MainMenuState::slotQuitFromApp()
{
    QApplication::quit();
}
