#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Explosion : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = 0);
    ~Explosion();
    enum { Type = UserType + 1 };
    int type() const;

private slots:
    void nextFrame();

private:
    void paint         (QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

private:
    QTimer * timer;
    QPixmap *spriteImage;
    int      currentFrame;
};

#endif // EXPLOSION_H
