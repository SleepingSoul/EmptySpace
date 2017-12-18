#include "aboutstate.h"
#include <QGraphicsView>
#include "aboutscene.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QMediaPlayer>
#include <QTimer>
#include <QIcon>
#include <QPixmap>
#include <QRegion>
#include <QVBoxLayout>
#include <QWidget>
#include "gamewindow.h"
#include "templates.h"
#include "sounds.h"
#include <QLabel>

AboutState::AboutState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd)
{
    /*Allocating memory for scene*/
    pabout_scene = new AboutScene(wwidth, wheight);

    /*Allocate memory and set up view*/
    pgraphics_view = new QGraphicsView;
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene                    (pabout_scene);

    /*Set up music*/
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    /*Set up about text*/
    QGraphicsTextItem *text = pabout_scene->addText("This program had been fully made by \n"
                                                    "NTUU_KPI::FICT::IK-62 student of second year\n"
                                                    "Katolikian Tihran. \nContacts: \n"
                                                    "Telegram: @ever_last_1ng \n"
                                                    "Facebook: /tihran.katolikian.3\n"
                                                    "\n"
                                                    "                                           All rights reserved.");
    QFont font;
    font.setBold(true);
    font.setPointSize(25);
    text->setPos(200, 200);
    text->setFont(font);
    text->setDefaultTextColor(Qt::white);

    /*Set up layout*/
    lout = new QGridLayout;
    lout->setContentsMargins(0, 0, 0, 0);
    lout->addWidget(pgraphics_view);

    /*Allocate memory and set up buttons*/
    btn_menu = new QPushButton;
    setUpButton(btn_menu, "btnBackMenu.png");

    QGraphicsProxyWidget *proxy_back_menu = pabout_scene->addWidget(btn_menu);
    proxy_back_menu->setPos(50, 50);
    connect(btn_menu, SIGNAL(clicked(bool)), SLOT(slotBtnMenuClicked()));

    timer_before_change = new QTimer(this);

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout   (lout);
}

AboutState::~AboutState()
{

}

QWidget *AboutState::getStateWidget() const
{
    return state_widget;
}
void AboutState::slotBtnMenuClicked()
{
    player->play();
    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotMenuState()));
    timer_before_change->start(CHANGE_T_MS);
}

void AboutState::slotMenuState()
{
    timer_before_change->stop();
    player->stop();

    /*We disconnect this, because if next time user will be there, this connection would be
     * already enabled and we  would connect it second time. As a result, we would had 2 main menu state calls. */
    disconnect(timer_before_change, SIGNAL(timeout()), this, SLOT(slotMenuState()));

    game_window->setState(State::MainMenu);
}
