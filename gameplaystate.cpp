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
#include "gameinfoevent.h"
#include "gameeventofappearing.h"
#include "infowindow.h"
#include "heavyenemy.h"
#include "warpeffect.h"

#define CHANGE_T_MS 250

/*TODO add alternative weapon, add alternative enemy, add charge, add other bonus except of healing*/
/*TODO find cause of exception*/

GameplayState::GameplayState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd)
{
    /*Scene ,view and Hero initializing*/
    pgraphics_view =  new GameView;
    pgraphics_scene = new GameScene(wwidth, wheight, gwd->getPictureFromCache(Pictures::GameplayMap12000x12000));
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
    pgraphics_view->setSceneRect                (500 - wwidth / 2., 500 - wheight / 2., wwidth - 2, wheight - 100);
    pgraphics_scene->setSceneRect               (0, 0, 10000, 10000);
    pgraphics_view->setFixedSize                (wwidth - 2, wheight - 100);
    pgraphics_view->setMouseTracking            (true);
    pgraphics_view->setCursor                   (QCursor(QPixmap("media/game_cursor.png")));

    pgraphics_scene->setView(pgraphics_view);

    phero->setPos            (500, 500);
    phero->setZValue         (2);
    phero->setRotation       (90);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->setHero (phero);

    connect(pgraphics_scene, SIGNAL(signalTargetCoordinate()),
            phero,           SLOT  (slotTarget()));
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
    setUpButton(btn_to_menu, "media/btnBackMenu.png");

    btn_pause = new QPushButton;
    setUpButton(btn_pause, "media/btnPause.png");

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
    change_time_timer->start(500);

    /*Events set up*/
    Enemy::setHero(phero);
    makeEvents();

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout   (lout);
    QPalette palette;
    QBrush brush;
    brush.setTexture(QPixmap("media/panel_texture.jpg"));
    palette.setBrush(QPalette::Background, brush);
    state_widget->setAutoFillBackground(true);
    state_widget->setPalette(palette);

    /*event activation*/
    slotButtonPauseClicked();
    //events.at(0)->executeEvent(pgraphics_scene);
}

GameplayState::~GameplayState()
{
    qDeleteAll(events);
    delete lbl_time;
    delete change_time_timer;
    delete timer_before_change;
    delete player;
    delete btn_pause;
    delete btn_to_menu;
    delete phero;
    delete lout;
    delete pgraphics_scene;
    delete pgraphics_view;
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

    setUpButton(btnOk, "media/btnYesQuit.png");
    setUpButton(btnNo, "media/btnCancel.png");

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
        btn_pause->setIcon(QIcon(QPixmap("media/btnPause.png")));
        paused = false;
        foreach (auto item, pgraphics_scene->items()) {
            dynamic_cast <GameplayItem *>(item)->startTime();
        }
    }
    else {
        btn_pause->setIcon(QIcon(QPixmap("media/btnPlay.png")));
        paused = true;
        foreach (auto item, pgraphics_scene->items()) {
            qDebug() << "helllo word";
            dynamic_cast <GameplayItem *>(item)->stopTime();
        }
    }
}

void GameplayState::slotUpdateTime()
{
    auto str = QDateTime::currentDateTime().time().toString();
    QString hours(str.left(2));
    QString mins(str.mid(3, 2));
    lbl_time->setText(hours + " : " + mins);

    executeEvents();
}

void GameplayState::executeEvents()
{
    foreach (auto event, events) {
        if (!event->executed() && event->cause(pgraphics_view)) {
            event->executeEvent(pgraphics_scene);
        }
    }
}

void GameplayState::makeEvents()
{
    /*Gameplay events take place in this function*/

    GameInfoEvent *first_info_event = new GameInfoEvent();
    first_info_event->setCausePoint({1500, 1000});
    InfoWindow *i_window = new InfoWindow(350, 200);
    i_window->setInfoText("Welcome, commander. You are a pilot of spaceship.\n "
                          "Control it with buttons \n W, A, S, D\n and mouse to "
                          "shoot. Sometimes i will help you to learn something new.\n "
                          "Good luck and have fun, comander!");
    first_info_event->setInfoWindow(i_window);
    events.push_back(first_info_event);

    GameEventOfAppearing *enemy_1_apr = new GameEventOfAppearing;
    GameEventOfAppearing *enemy_2_apr = new GameEventOfAppearing;
    enemy_1_apr->setCausePoint({2050, 600});
    enemy_2_apr->setCausePoint({2050, 600});

    WarpEffect *enemy_1_warp = new WarpEffect(new Enemy());
    WarpEffect *enemy_2_warp = new WarpEffect(new Enemy());
    //Enemy *enemy_1 = new Enemy();
    //Enemy *enemy_2 = new Enemy();
    enemy_1_warp->setPos(2000, 400);
    enemy_2_warp->setPos(2000, 800);

    enemy_1_apr->setAppearingItem(enemy_1_warp);
    enemy_2_apr->setAppearingItem(enemy_2_warp);

    events.push_back(enemy_1_apr);
    events.push_back(enemy_2_apr);

    GameInfoEvent *first_enemies_event = new GameInfoEvent();
    first_enemies_event->setCausePoint({2055, 600});
    InfoWindow *i2_window = new InfoWindow(350, 200);
    i2_window->setInfoText("It looks like you have just met your first enemies. Be carefull!\n"
                           "Try to use clever tactic and not to take damage");
    first_enemies_event->setInfoWindow(i2_window);
    events.push_back(first_enemies_event);

    GameInfoEvent *heal_event = new GameInfoEvent();
    heal_event->setCausePoint({2500, 600});
    InfoWindow *he_window = new InfoWindow(350, 200);
    he_window->setInfoText("After enemy die - you can collect some bonuses which had been "
                           "left by enemies on the space. Fox example, you can charge your "
                           "HP with this healing items!");
    heal_event->setInfoWindow(he_window);
    events.push_back(heal_event);

    GameEventOfAppearing *enemy_3_apr = new GameEventOfAppearing;
    GameEventOfAppearing *enemy_4_apr = new GameEventOfAppearing;
    GameEventOfAppearing *enemy_5_apr = new GameEventOfAppearing;
    GameEventOfAppearing *enemy_6_apr = new GameEventOfAppearing;
    enemy_3_apr->setCausePoint({4600, 600});
    enemy_4_apr->setCausePoint({4600, 600});
    enemy_5_apr->setCausePoint({4600, 600});
    enemy_6_apr->setCausePoint({4600, 600});

    WarpEffect *enemy_3_w = new WarpEffect(new Enemy());
    WarpEffect *enemy_4_w = new WarpEffect(new Enemy());
    WarpEffect *enemy_5_w = new WarpEffect(new Enemy());
    WarpEffect *enemy_6_w = new WarpEffect(new Enemy());

    enemy_3_w->setPos(4000, 500);
    enemy_4_w->setPos(4100, 800);
    enemy_5_w->setPos(3900, 600);
    enemy_6_w->setPos(4000, 1000);

    enemy_3_apr->setAppearingItem(enemy_3_w);
    enemy_4_apr->setAppearingItem(enemy_4_w);
    enemy_5_apr->setAppearingItem(enemy_5_w);
    enemy_6_apr->setAppearingItem(enemy_6_w);

    events.push_back(enemy_3_apr);
    events.push_back(enemy_4_apr);
    events.push_back(enemy_5_apr);
    events.push_back(enemy_6_apr);

    GameInfoEvent *boss_is_near_event = new GameInfoEvent();
    boss_is_near_event->setCausePoint({5500, 600});
    InfoWindow *bin_window = new InfoWindow(350, 200);
    bin_window->setInfoText("Get ready to met something heavier than this little "
                            "spaceships. On our radar we see something big and, "
                            "perhaps, very dangerous to you! It would be better to "
                            "use your alternative plasma weapon and shield. You may activate shield only "
                            "once with button \"q\".");
    boss_is_near_event->setInfoWindow(bin_window);
    events.push_back(boss_is_near_event);

    GameEventOfAppearing *boss_apr = new GameEventOfAppearing;
    boss_apr->setCausePoint({6000, 600});

    HeavyEnemy *boss = new HeavyEnemy();

    boss->setPos(7500, 600);

    boss_apr->setAppearingItem(boss);

    events.push_back(boss_apr);

    GameEventOfAppearing *boss1_apr = new GameEventOfAppearing;
    boss1_apr->setCausePoint({8500, 1500});

    HeavyEnemy *boss1 = new HeavyEnemy();

    boss1->setPos(8500, 1500);

    boss1_apr->setAppearingItem(boss1);

    events.push_back(boss1_apr);
}
