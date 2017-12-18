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
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    QPixmap cursor_pic;
};

#endif // GAMEVIEW_H
