#include "gameplaystate.h"
#include "gamewindow.h"
#include "sizes.h"
#include <QWidgetItem>
#include "sounds.h"
#include <QGraphicsProxyWidget>
#include "quitwindow.h"
#include "quitwindow.h"
#include "gamescene.h"
#include "QGraphicsView"
#include "hero.h"
#include "state.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include "gameview.h"

#define CHANGE_T_MS 250

GameplayState::GameplayState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd)
{
    /*Scene ,view and Hero initializing*/
    pgraphics_view =  new GameView;
    pgraphics_scene = new GameScene(wwidth, wheight);
    phero = new Hero;

    /*View set up*/
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    /*important setting! we forbid
     our graphics view call update
     when some item change it's
     coords*/
    pgraphics_view->setViewportUpdateMode       (QGraphicsView::NoViewportUpdate);
    pgraphics_view->setScene                    (pgraphics_scene);
    pgraphics_view->setSceneRect                (0, 0, wwidth, wheight);
    pgraphics_scene->setSceneRect               (0, 0, 10000, 10000);
    pgraphics_view->setMouseTracking(true);
    pgraphics_view->setCursor(QCursor(QPixmap("game_cursor.png")));

    phero->setPos            (500, 500);
    phero->setZValue         (1);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->setHero(phero);

    connect(pgraphics_scene, SIGNAL(signalTargetCoordinate(QPointF)),
            phero,           SLOT  (slotTarget(QPointF)));
    connect(pgraphics_scene, SIGNAL(signalShot(bool)),
            phero,           SLOT  (slotShot(bool)));
    connect(pgraphics_scene, SIGNAL(signalButtons(QSet <Qt::Key>&)),
            phero,           SLOT  (slotButtons(QSet <Qt::Key>&)));

    /*Layout set up*/
    lout = new QVBoxLayout;
    //QWidget *wgt = new QWidget;
    lout->setContentsMargins(0, 0, 0, 0);

    /*Buttons set up*/
    btn_to_menu = new QPushButton;
    btn_to_menu->setIcon(QIcon(QPixmap("btnBackMenu.png")));
    btn_to_menu->setIconSize(QSize(240, 52.12));
    btn_to_menu->setFixedSize(240, 52.12);

    QRegion reg(QPolygon() << QPoint(0,10) << QPoint(10, 0) << QPoint(240, 0) << QPoint(240, 42.12) <<
                QPoint(230, 52.12) << QPoint(0, 52.12));

    btn_to_menu->setMask(reg);

    connect(btn_to_menu, SIGNAL(clicked(bool)), SLOT(slotButtonToMenuClicked()));
    lout->addWidget(btn_to_menu);
    lout->addWidget(pgraphics_view);

    btn_quit = new QPushButton;
    btn_quit->setFixedSize(175, 50);

    btn_dont_quit = new QPushButton;
    btn_dont_quit->setFixedSize(175, 50);

    /*Sounds set up*/
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    timer_before_change = new QTimer(this);

//    QGraphicsProxyWidget *proxyBtnMenu = pgraphics_scene->addWidget(btn_to_menu);
//    proxyBtnMenu->setPos   (50, 50);
//    proxyBtnMenu->setZValue(5);     //it is how we will recognize this button on the scene

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout   (lout);
    QPalette palette;
    QBrush brush;
    brush.setTexture(QPixmap("panel_texture.jpg"));
    palette.setBrush(QPalette::Background, brush);
    state_widget->setAutoFillBackground(true);
    state_widget->setPalette(palette);
    QCursor cursor(QPixmap("menu_cursor.png"));
    state_widget->setCursor(cursor);

    btn_to_menu->setCursor(cursor);
}

GameplayState::~GameplayState()
{
    delete lout;
    delete player;
    delete pgraphics_view;
    delete pgraphics_scene;
}

QWidget *GameplayState::getStateWidget() const
{
    return state_widget;
}

QGraphicsView *GameplayState::getScene() const
{
    return pgraphics_view;
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
    proxy_btn_ok->setPos(QPoint(wwidth / 2. - 100 - 175./2, wheight / 2. + 50));
    proxy_btn_no->setPos(QPoint(wheight / 2. + 100 - 175./2, wheight / 2. + 50));
    proxy_btn_ok->setZValue(5);
    proxy_btn_no->setZValue(5);

}

void GameplayState::slotMenuState()
{
    //qDebug() << "Set menu state from GameplayState called.";
    timer_before_change->stop();
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotMenuState()));
    pgraphics_scene->removeItem(quit_window);
    pgraphics_scene->removeItem(proxy_btn_ok);
    pgraphics_scene->removeItem(proxy_btn_no);
    game_window->setState(State::MainMenu);
}

void GameplayState::quitHandler()
{
    quit_window = new QuitWindow();
    pgraphics_scene->addItem(quit_window);
    quit_window->setPos(QPoint(wwidth / 2., wheight / 2.));
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
