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
#include <QTimer>
#include <QPair>
#include "decoration.h"
#include "hero.h"
#include "herothrust.h"
#include "bullet.h"

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(const int w, const int h, QObject *parent = 0);
    ~CustomScene();

    void set_hero              (Hero *);                    //set hero pointer to have oportuniy to move it
    void set_hero_thrust       (HeroThrust *);              //set hero thrust to have oportunity to rotate it
    void set_background        (const QPixmap);             //set background picture
    void read_decorations      (const QString);             //read decoration polygons from file
    void set_offset_change_flag(const bool);
    void push_pbullet          (Bullet *);

signals:
    void signalTargetCoordinate(QPointF);
    void signalShot            (bool);

public slots:
    void slotChangeOffsetChangedFlag (bool);
    void slotProcessBulletDestruction(QPair <Bullet::destr_type, Bullet *>);
    void slotMoveBackground          (dir);

private slots:
    void slotUpdateViewport();                                    //slot which controls program FPS.

private /*functions*/:
    void mouseMoveEvent   (QGraphicsSceneMouseEvent *) override;      //Mouse tracking
    //void keyPressEvent    (QKeyEvent *)                override;      //Key tracking
    //void keyReleaseEvent  (QKeyEvent *)                override;      //Key release control
    void mousePressEvent  (QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void drawBackground   (QPainter *, const QRectF &) override;      //function that draws BG
    void targetCoordinate (QPointF);                                  //To set hero angle straight to cursor
    void move_hero_x      (const int);                                //moves hero and thrust
    void move_hero_y      (const int);

private /*objects*/:
    QVector <Decoration *> dec_vec;             //vector which contains all Decorations
    QSet <Qt::Key>         pr_keys;             //set which contains all legal pressed and not released keys
    int                    hor_offset;          //horizintal offset of the scene
    int                    ver_offset;          //vertical offset of the scene
    const int              WIDTH;
    const int              HEIGHT;
    const int              STEP;
    QPixmap                bg_image;
    bool                   offsets_changed;
    dir                    offsets_dir;
    bool                   mouseClicked;
    QTimer*                fps_timer;
    QPointF                target;
    double                 robot_angle;

    Hero *phero;
    HeroThrust *phthrust;
};

#endif // CUSTOMSCENE_H
