#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class QTimer;

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();
    ~GameView();

private:
    QPixmap cursor_pic;
};

#endif // GAMEVIEW_H
