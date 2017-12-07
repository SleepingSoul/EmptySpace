#include "gameview.h"
#include <QTimer>
#include <QDebug>

GameView::GameView()
{
    cursor_pic.load("game_cursor.png");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotRotateCursor()));
}

GameView::~GameView()
{

}

void GameView::focusInEvent(QFocusEvent *event)
{
    static int x;
    qDebug() << "Focus in " << ++x;;
    timer->start(100);
    QGraphicsView::focusInEvent(event);
}

void GameView::focusOutEvent(QFocusEvent *event)
{
    static int x;
    qDebug() << "Focus out " << ++x;
    timer->stop();
    QGraphicsView::focusOutEvent(event);
}

void GameView::slotRotateCursor()
{
    static qreal x;
    while (x > 360) x -= 360;
    QCursor cursor(cursor_pic.transformed(QTransform().rotate(++x)));
    this->setCursor(cursor);
}
