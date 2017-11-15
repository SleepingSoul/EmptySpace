#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <cassert>
#include <cstdlib>
#include "hero.h"
#include "decoration.h"

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();
    void set_hero_coords(const int, const int);
    void set_hero(Hero *);
    void set_size(const int, const int);

signals:
    // Signal for throwing cursor position
    void signalTargetCoordinate(QPointF point);

public slots:
    void slotMoveBackground(dir);                                           //Slot for moving the background
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;               //Mouse tracking
    void keyPressEvent(QKeyEvent *) override;                               //Key tracking
    void drawBackground(QPainter *, const QRectF &) override;
    int hor_offset;
    int ver_offset;
    QVector <Decoration *> dec_vec;
    QVector <Decoration *> temp_decs;
    Hero *phero;                                                            //Hero pointer (main scene object so req.)
    int WIDTH;
    int HEIGHT;
};

#endif // CUSTOMSCENE_H
