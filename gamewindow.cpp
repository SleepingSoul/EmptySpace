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
    pgraphics_view->setViewportUpdateMode       (QGraphicsView::NoViewportUpdate);  /*important setting! we forbid
                                                                                      our graphics view call update
                                                                                      when some item change it's
                                                                                      coords*/

    pgraphics_view->setScene        (pgraphics_scene);
    pgraphics_view->setSceneRect    (0, 0, 1000, 600);
    pgraphics_scene->setSceneRect   (0, 0, 1000, 600);
    pgraphics_view->setMouseTracking(true);

    phero = new Hero;
    phero->setPos            (500, 500);
    phero->setZValue         (1);
    pgraphics_scene->addItem (phero);
    pgraphics_scene->set_hero(phero);

    connect(pgraphics_scene, SIGNAL(signalTargetCoordinate(QPointF)),
            phero,           SLOT  (slotTarget(QPointF)));
    connect(phero,           SIGNAL(moveBackground(dir)),
            pgraphics_scene, SLOT  (slotMoveBackground(dir)));
    connect(pgraphics_scene, SIGNAL(signalShot(bool)),
            phero,           SLOT(slotShot(bool)));
}

GameWindow::~GameWindow()
{

}
