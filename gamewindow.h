#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include "customscene.h"
#include "hero.h"
#include "herothrust.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private:
    CustomScene *pgraphics_scene;      //QGraphicsScene
    QGraphicsView *pgraphics_view;     //QGraphicsView
    Hero *phero;                        //Hero pointer
};

#endif // GAMEWINDOW_H
