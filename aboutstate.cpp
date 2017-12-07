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
#include "gamewindow.h"

AboutState::AboutState(const int ww, const int wh)
    : wwidth(ww), wheight(wh)
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

    /*Set up layout*/
    lout = new QGridLayout;
    lout->setContentsMargins(0, 0, 0, 0);
    lout->addWidget(pgraphics_view);

    /*Allocate memory and set up buttons*/
    btn_menu = new QPushButton;
    btn_menu->setIcon(QIcon(QPixmap("btnBackMenu.png")));
    btn_menu->setIconSize(QSize(240, 52.12));
    btn_menu->setFixedSize(240, 52.12);

    /*This is shape for my custom button*/
    QRegion reg(QPolygon() << QPoint(0,10) << QPoint(10, 0) << QPoint(240, 0) << QPoint(240, 42.12) <<
                QPoint(230, 52.12) << QPoint(0, 52.12));

    btn_menu->setMask(reg);

    QGraphicsProxyWidget *proxy_back_menu = pabout_scene->addWidget(btn_menu);
    proxy_back_menu->setPos(50, 50);

    timer_before_change = new QTimer(this);
}

AboutState::~AboutState()
{

}

QWidget *AboutState::getStateWidget() const
{

}
void AboutState::slotBtnMenuClicked()
{

}

void AboutState::slotMenuState()
{

}
