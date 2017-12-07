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
    QTimer *timer;
    QPixmap cursor_pic;

private slots:
    void slotRotateCursor();
};

#endif // GAMEVIEW_H
