#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent)
{
    // Setting up main window params
    this->resize      (1000, 600);
    this->setFixedSize(1000, 600);

    pgraphics_view =  new QGraphicsView(this);                                 //graphics view
    pgraphics_scene = new CustomScene  (1000, 600);                            //custom graphics scene

    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pgraphics_view->setScene        (pgraphics_scene);
    pgraphics_view->setSceneRect    (0, 0, 1000, 600);
    pgraphics_view->setMouseTracking(true);

    phero = new Hero;
    phero->setPos            (500, 500);
    phero->setZValue         (1);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->set_hero(phero);

    phthrust = new HeroThrust;
    phthrust->setPos                (500, 500);
    phthrust->setZValue             (0);
    pgraphics_scene->addItem        (phthrust);
    pgraphics_scene->set_hero_thrust(phthrust);

    connect(pgraphics_scene, SIGNAL(transfer_HeroMovingState_to_HeroThrust(bool)),
            phthrust,        SLOT  (slotSetMoving(bool)));
    connect(pgraphics_scene, SIGNAL(transfer_HeroDirecion_to_HeroThrust(dir)),
            phthrust,        SLOT  (slotSetDirection(dir)));
}

GameWindow::~GameWindow()
{

}
