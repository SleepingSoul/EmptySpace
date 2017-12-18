#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QList>

class QPixmap;
class Decoration;
class Hero;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(const int, const int, QObject * = 0);
    ~GameScene();

    void readDecorations(const QString);             //read decoration polygons from file
    void setHero(Hero *);

signals:
    void signalTargetCoordinate(QPointF);
    void signalShot            (bool);
    void signalButtons         (QSet <Qt::Key> &);

private slots:
    void slotUpdateViewport();                                    //slot which controls program FPS.

private /*functions*/:
    void mouseMoveEvent   (QGraphicsSceneMouseEvent *) override;    //Mouse tracking;
    void keyPressEvent    (QKeyEvent *)                override;    //Key tracking;
    void keyReleaseEvent  (QKeyEvent *)                override;    //Key release control;
    void mousePressEvent  (QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void drawBackground   (QPainter *, const QRectF &) override;     //function that draws BG;
    void targetCoordinate (QPointF);                                 //To set hero angle straight to cursor;

private /*objects*/:
    Hero *phero;
    QList <Decoration *>   dec_list;            //vector which contains all Decorations;
    QSet <Qt::Key>         pr_keys;             //set which contains all legal pressed and not released keys;
    QPixmap                *bg_image;
    QTimer                 *fps_timer;
    QPointF                target;
    qreal                  hero_angle;
    const int              wwidth;
    const int              wheight;
    const int              STEP {3};
};

#endif // GAMESCENE_H
