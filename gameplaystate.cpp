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
#include "gameplayitem.h"
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QStyle>
#include "templates.h"
#include "hpline.h"

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
    pgraphics_view->setSceneRect                (0, 0, wwidth - 2, wheight - 150);
    pgraphics_scene->setSceneRect               (0, 0, 10000, 10000);
    pgraphics_view->setMouseTracking            (true);
    pgraphics_view->setCursor(QCursor(QPixmap("game_cursor.png")));

    pgraphics_scene->setView(pgraphics_view);

    phero->setPos            (500, 500);
    phero->setZValue         (2);
    phero->setRotation       (90);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->setHero (phero);

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
    setUpButton(btn_to_menu, "btnBackMenu.png");

    btn_pause = new QPushButton;
    setUpButton(btn_pause, "btnPause.png");

    /*Date/time*/
    lbl_time = new QLabel(QDateTime::currentDateTime().time().toString());
    QFont font("Museo Slab");
    lbl_time->setStyleSheet("QLabel {color: white;}");
    font.setPointSize(16);
    font.setBold(true);
    lbl_time->setFont(font);

    /*Header layout*/
    QHBoxLayout *header = new QHBoxLayout;
    header->addWidget(btn_to_menu, 1, Qt::AlignLeft);
    header->addWidget(lbl_time, 1, Qt::AlignCenter);
    header->addWidget(btn_pause, 1, Qt::AlignRight);

    /*Connections*/
    connect(btn_to_menu, SIGNAL(clicked(bool)), SLOT(slotButtonToMenuClicked()));
    connect(btn_pause, SIGNAL(clicked(bool)), SLOT(slotButtonPauseClicked()));

    /*Set up main layout*/
    lout->addLayout(header);
    lout->addWidget(pgraphics_view);


    /*Sounds set up*/
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    timer_before_change = new QTimer(this);
    change_time_timer = new QTimer(this);
    connect(change_time_timer, SIGNAL(timeout()), SLOT(slotUpdateTime()));
    change_time_timer->start(1000);


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

QGraphicsView *GameplayState::getView() const
{
    return pgraphics_view;
}

void GameplayState::slotButtonToMenuClicked()
{
    btn_to_menu->setEnabled(false);

    if (!paused)
        slotButtonPauseClicked(); //pause

    //We disable button pause to avoid enabling game during quit window exists
    btn_pause->setEnabled(false);

    quit_window = new QuitWindow;
    pgraphics_scene->addItem(quit_window);

    int central_x(pgraphics_view->sceneRect().x() + pgraphics_view->sceneRect().width() / 2),
        central_y(pgraphics_view->sceneRect().y() + pgraphics_view->sceneRect().height() / 2),
               dx(quit_window->width() / 2), dy(quit_window->height() / 2);

    quit_window->setPos(central_x, central_y);
    quit_window->setZValue(5);

    QPushButton *btnOk = new QPushButton;
    QPushButton *btnNo = new QPushButton;

    setUpButton(btnOk, "btnYesQuit.png");
    setUpButton(btnNo, "btnCancel.png");

    proxy_btn_ok = pgraphics_scene->addWidget(btnOk);
    proxy_btn_no = pgraphics_scene->addWidget(btnNo);

    proxy_btn_ok->setPos(central_x - dx + 40, central_y + dy - btnOk->height() - 40);
    proxy_btn_no->setPos(central_x + dx - 40 - btnNo->width(), central_y + dy - btnOk->height() - 40);

    proxy_btn_ok->setZValue(5);
    proxy_btn_no->setZValue(5);

    connect(btnOk, SIGNAL(clicked(bool)), SLOT(slotQuitConfirmed()));
    connect(btnNo, SIGNAL(clicked(bool)), SLOT(slotDontQuit()));
}

void GameplayState::slotMenuState()
{

    //we enable pause button now (it was disabled yet, during quit window existing period)
    btn_pause->setEnabled(true);
    btn_to_menu->setEnabled(true);

    timer_before_change->stop();

    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotMenuState()));

    pgraphics_scene->removeItem(quit_window);
    pgraphics_scene->removeItem(proxy_btn_ok);
    pgraphics_scene->removeItem(proxy_btn_no);

    game_window->setState(State::MainMenu);
}

void GameplayState::quitHandler()
{

}

void GameplayState::slotQuitConfirmed()
{  
    player->play();
    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotMenuState()));
    timer_before_change->start(CHANGE_T_MS);
}

void GameplayState::slotDontQuit()
{
    //we enable pause button now (it was disabled yet, during quit window existing period)
    btn_pause->setEnabled(true);
    btn_to_menu->setEnabled(true);

    pgraphics_scene->removeItem(quit_window);
    pgraphics_scene->removeItem(proxy_btn_ok);
    pgraphics_scene->removeItem(proxy_btn_no);

    //Set off pause
    this->slotButtonPauseClicked();
}

void GameplayState::slotButtonPauseClicked()
{
    if (paused) {
        pgraphics_view->setFocus();
        btn_pause->setIcon(QIcon(QPixmap("btnPause.png")));
        paused = false;
        foreach (auto item, pgraphics_scene->items()) {
            dynamic_cast <GameplayItem *>(item)->startTime();
        }
    }
    else {
        btn_pause->setIcon(QIcon(QPixmap("btnPlay.png")));
        paused = true;
        foreach (auto item, pgraphics_scene->items()) {
            dynamic_cast <GameplayItem *>(item)->stopTime();
        }
    }
}

void GameplayState::slotUpdateTime()
{
    static bool flag(false);
    auto str = QDateTime::currentDateTime().time().toString();
    QString hours(str.left(2));
    QString mins(str.mid(3, 2));
    lbl_time->setText(hours + " " + (flag? ":" : " ") + " " + mins);
    flag = !flag;
}
