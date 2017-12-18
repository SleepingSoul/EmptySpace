#include "gameview.h"
#include <QTimer>
#include <QDebug>

GameView::GameView()
{
    cursor_pic.load("game_cursor.png");
}

GameView::~GameView()
{

}

void GameView::focusInEvent(QFocusEvent *event)
{
    QGraphicsView::focusInEvent(event);
}

void GameView::focusOutEvent(QFocusEvent *event)
{
    QGraphicsView::focusOutEvent(event);
}
