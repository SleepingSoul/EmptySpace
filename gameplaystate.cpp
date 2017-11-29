#include "gameplaystate.h"
#include "gamewindow.h"
#include "sizes.h"
#include <QWidgetItem>
#include "sounds.h"
#include <QGraphicsProxyWidget>
#include "quitwindow.h"
#include "quitwindow.h"

#define CHANGE_T_MS 250

GameplayState::GameplayState(GameWindow *gw)
    : _gw(gw)
{
    pgraphics_view =  new QGraphicsView;
    pgraphics_scene = new CustomScene  (WWIDTH, WHEIGHT);
    phero = new Hero;

    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    /*important setting! we forbid
     our graphics view call update
     when some item change it's
     coords*/
    pgraphics_view->setViewportUpdateMode       (QGraphicsView::NoViewportUpdate);
    pgraphics_view->setScene        (pgraphics_scene);
    pgraphics_view->setSceneRect    (0, 0, WWIDTH, WHEIGHT);
    pgraphics_scene->setSceneRect   (0, 0, WWIDTH, WHEIGHT);
    pgraphics_view->setMouseTracking(true);

    phero->setPos            (500, 500);
    phero->setZValue         (1);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->set_hero(phero);

    connect(pgraphics_scene, SIGNAL(signalTargetCoordinate(QPointF)),
            phero,           SLOT  (slotTarget(QPointF)));
    connect(phero,           SIGNAL(moveBackground(dir)),
            pgraphics_scene, SLOT  (slotMoveBackground(dir)));
    connect(pgraphics_scene, SIGNAL(signalShot(bool)),
            phero,           SLOT  (slotShot(bool)));

    lout = new QVBoxLayout;
    lout->setContentsMargins(0, 0, 0, 0);
    lout->addWidget         (pgraphics_view);

    btn_to_menu = new QPushButton;
    btn_to_menu->setIcon(QIcon(QPixmap("btn_tomenu.png")));
    btn_to_menu->setIconSize(QSize(175, 50));
    btn_to_menu->setFixedSize(175, 50);
    connect(btn_to_menu, SIGNAL(clicked(bool)), SLOT(slotButtonToMenuClicked()));

    btn_quit = new QPushButton;
    btn_quit->setFixedSize(175, 50);

    btn_dont_quit = new QPushButton;
    btn_dont_quit->setFixedSize(175, 50);

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    timer_before_change = new QTimer(this);

    QGraphicsProxyWidget *proxyBtnMenu = pgraphics_scene->addWidget(btn_to_menu);
    proxyBtnMenu->setPos(50, 50);
    proxyBtnMenu->setZValue(5);     //it is how we will recognize this button on the scene
}

GameplayState::~GameplayState()
{
    delete lout;
    delete player;
    delete pgraphics_view;
    delete pgraphics_scene;
}

void GameplayState::buildWindowState(GameWindow *gwp)
{
    /*Set up size. It can be unnesesary if we
     * use only size for every state*/
    gwp->resize      (WWIDTH, WHEIGHT);
    gwp->setFixedSize(WWIDTH, WHEIGHT);

    /*Set up out layout*/
    gwp->setLayout(lout);
}

void GameplayState::slotButtonToMenuClicked()
{
    quitHandler();
    QPushButton *btnOk = new QPushButton("Ok");
    QPushButton *btnNo = new QPushButton("No");
    btnOk->setFixedSize(175, 50);
    btnNo->setFixedSize(175, 50);
    connect(btnOk, SIGNAL(clicked(bool)), SLOT(slotQuitConfirmed()));
    connect(btnNo, SIGNAL(clicked(bool)), SLOT(slotDontQuit()));

    proxy_btn_ok = pgraphics_scene->addWidget(btnOk);
    proxy_btn_no = pgraphics_scene->addWidget(btnNo);
    proxy_btn_ok->setPos(QPoint(CENTRAL_X - 100 - 175.F/2, CENTRAL_Y + 50));
    proxy_btn_no->setPos(QPoint(CENTRAL_X + 100 - 175.F/2, CENTRAL_Y + 50));
    proxy_btn_ok->setZValue(5);
    proxy_btn_no->setZValue(5);
//    player->play();
//    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotMenuState()));
//    timer_before_change->start(CHANGE_T_MS);
}

void GameplayState::slotMenuState()
{
    _gw->setState(State::MainMenu);
}

void GameplayState::quitHandler()
{
    quit_window = new QuitWindow();
    pgraphics_scene->addItem(quit_window);
    quit_window->setPos(QPoint(CENTRAL_X, CENTRAL_Y));
    quit_window->setZValue(5);
}

void GameplayState::slotQuitConfirmed()
{
    player->play();
    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotMenuState()));
    timer_before_change->start(CHANGE_T_MS);
}

void GameplayState::slotDontQuit()
{
    pgraphics_scene->removeItem(quit_window);
    pgraphics_scene->removeItem(proxy_btn_ok);
    pgraphics_scene->removeItem(proxy_btn_no);
}
