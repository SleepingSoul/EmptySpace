#include "gamewindow.h"
#include "hero.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent)
{
    // Setting up main window params
    this->resize(1000, 600);
    this->setFixedSize(1000, 600);

    pgraphics_scene = new CustomScene;             //custom graphics scene
    pgraphics_view = new QGraphicsView(this);      //graphics view

    pgraphics_view->setRenderHint(QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pgraphics_view->setScene(pgraphics_scene);
    pgraphics_view->setSceneRect(0, 0, 1000, 600);
    pgraphics_scene->set_size(1000, 600);               //setting up the main sizes of scene
    pgraphics_view->setMouseTracking(true);

    phero = new Hero;
    phero->setPos(500, 500);
    pgraphics_scene->set_hero_coords(500, 500);
    pgraphics_scene->addItem(phero);

    pgraphics_scene->set_hero(phero);

    connect(pgraphics_scene, SIGNAL(signalTargetCoordinate(QPointF)), phero, SLOT(slotTarget(QPointF)));
    connect(phero, SIGNAL(moveBackground(dir)), pgraphics_scene, SLOT(slotMoveBackground(dir)));
}

GameWindow::~GameWindow()
{

}
