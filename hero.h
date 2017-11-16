#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

//direction
enum dir{TOP = 0, RIGHT, BOT, LEFT};                                                /*Enumeration for
                                                                                    directing the Hero's movings*/

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

signals:
    void moveBackground(dir);                                                       /*Signal to move the background
                                                                                    depending on hero movings*/
    void changeOffsetFlag(bool);
public slots:
    void slotTarget(QPointF point);                                                 /*Slot receiving the position
                                                                                    of cursor*/
private:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;   //Paint the hero
    QPainterPath shape() const override;                                            //For collisions

private slots:
    void slotGameTimer();

private:
    QTimer *gameTimer;                                                              //Main game timer
    QPointF target;                                                                 //Cursor position
};

#endif // HERO_H
