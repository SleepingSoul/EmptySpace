#include "MainMenuState.h"
#include "gamewindow.h"
#include "gameplaystate.h"
#include "sizes.h"

#define SELECT_SOUND "select_btn_sound.mp3"
#define CHANGE_T_MS 250

MainMenuState::MainMenuState()
{
    /*Allocate memory and set up of menu scene*/
    pmenu_scene = new MenuScene                 (WWIDTH, WHEIGHT);
    pmenu_scene->setSceneRect                   (0, 0, WWIDTH, WHEIGHT);
    pgraphics_view = new QGraphicsView          (pmenu_scene);

    /*Allocate memory and set up for graphics view widget, which will
     * contain out scene and will be built into our main "GameWidget"*/
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene                    (pmenu_scene);

    /*Set up music*/
    player = new QMediaPlayer;

    /*Allocate memory for buttons*/
    btnPlay = new QPushButton;
    btnSettings = new QPushButton;

    /*Set up buttons design*/
    btnPlay->setIcon         (QIcon(QPixmap("btn_play.png")));
    btnSettings->setIcon     (QIcon(QPixmap("btn_settings.png")));
    btnPlay->setIconSize     (QSize(175, 50));
    btnSettings->setIconSize (QSize(175, 50));
    btnPlay->setFixedSize    (175, 50);
    btnSettings->setFixedSize(175, 50);

    /*Make buttons proxy to built them into scene*/
    proxyPlay = pmenu_scene->addWidget    (btnPlay);
    proxySettings = pmenu_scene->addWidget(btnSettings);

    /*Set up position of buttons on the scene*/
    proxyPlay->setPos    (75, 200);
    proxySettings->setPos(proxyPlay->pos() + QPoint(0, 75));

    /*Connect buttons signals->this class slots to handle it*/
    connect(btnPlay,     SIGNAL(clicked(bool)), SLOT(slotButtonPlay()));
    connect(btnSettings, SIGNAL(clicked(bool)), SLOT(slotButtonSettings()));

    /*Allocate and set up layout*/
    lout = new QVBoxLayout;
    lout->addWidget(pgraphics_view);
    lout->setContentsMargins(0, 0, 0, 0);

    /*Allocate memory for timer, which will make a little pause after
     * button click till widget changes*/
    timerBeforeChange = new QTimer;
}

MainMenuState::~MainMenuState()
{
    /*Here we should carefully delete all dynamic memory we had allocated*/
    delete player;
    delete lout;
//    delete btnPlay;
//    delete btnSettings;
//    delete proxyPlay;
//    delete proxySettings; /*hope it's ok...*/
    delete timerBeforeChange;
    delete pgraphics_view;
    delete pmenu_scene;
}

void MainMenuState::buildWindowState(GameWindow *gwd)
{
    /*Firslty we mark the main widget pointer*/
    this->gwd = gwd;

    /*Than we resize this widget hot it requires our scene
     * (can be unnesesary if we use one size policy for all states*/
    gwd->resize      (WWIDTH, WHEIGHT);
    gwd->setFixedSize(WWIDTH, WHEIGHT);

    /*Set up layout*/
    gwd->setLayout(lout);

    /*Activate backgroung music*/
    player->play();
}

void MainMenuState::slotButtonPlay()
{
    /*If user clcked button "Play",
     * we stop the music,
     * enable click sound, w8
     * little amount of time and
     * than emit signal to change the
     * state of widget*/
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    /*We connect this timer to slot depends on required next state*/
    connect(timerBeforeChange, SIGNAL(timeout()), SLOT(slotGameplayState()));
    timerBeforeChange->start(CHANGE_T_MS);
}

void MainMenuState::slotGameplayState()
{
    /*Just stop timer and change state*/
    timerBeforeChange->stop();
    gwd->setState(State::Gameplay);
}

void MainMenuState::slotButtonSettings()
{
    player->stop();
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));
    player->play();

    connect(timerBeforeChange, SIGNAL(timeout()), SLOT(slotSettingsState()));
    timerBeforeChange->start(CHANGE_T_MS);
}

void MainMenuState::slotSettingsState()
{
    timerBeforeChange->stop();
    gwd->setState(State::Settings);
}
