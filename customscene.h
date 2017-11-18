#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <cassert>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>
#include <QtMath>
#include "hero.h"
#include "decoration.h"

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(const int w, const int h, QObject *parent = 0);
    ~CustomScene();

    void set_hero              (Hero *);                    //set hero pointer to have oportuniy to move it
    void set_background        (const QPixmap);             //set background picture
    void read_decorations      (const QString);             //read decoration polygons from file
    void set_offset_change_flag(const bool);

public slots:
    void slotChangeOffsetChangedFlag(bool);

private slots:
    void slotFPStimer();                                    //slot which controls program FPS.

private /*functions*/:
    void mouseMoveEvent  (QGraphicsSceneMouseEvent *) override;      //Mouse tracking
    void keyPressEvent   (QKeyEvent *)                override;      //Key tracking
    void keyReleaseEvent (QKeyEvent *)                override;      //Key release control
    void drawBackground  (QPainter *, const QRectF &) override;      //function that draws BG
    void targetCoordinate(QPointF);                                  //To set hero angle straight to cursor
    void moveBackground  (const dir);

private /*objects*/:
    QVector <Decoration *> dec_vec;     //vector which contains all Decorations
    QSet <Qt::Key> pr_keys;             //set which contains all legal pressed and not released keys
    int hor_offset;                     //horizintal offset of the scene
    int ver_offset;                     //vertical offset of the scene
    const int WIDTH;
    const int HEIGHT;
    const int STEP;
    QPixmap bg_image;
    bool offsets_changed;
    QTimer *fps_timer;
    QPointF target;
    double robot_angle;

    Hero *phero;
};

#endif // CUSTOMSCENE_H
