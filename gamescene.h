#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QList>
#include <QVector>

class QPixmap;
class Decoration;
class Hero;
class HpLine;
class MiniMap;
class Weapon;
class Charger;
class QGraphicsView;
class InfoWindow;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(const int, const int, const QPixmap *, QObject * = 0);
    ~GameScene();

    void readDecorations(const QString);             //read decoration polygons from file
    void setHero(Hero *);
    void setView(QGraphicsView *);
    void addInfoWindow(InfoWindow *);
    void popInfoWindow();

signals:
    void signalTargetCoordinate();
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

private /*objects*/:
    Hero *phero;
    QList <Decoration *>   dec_list;            //vector which contains all Decorations;
    QSet <Qt::Key>         pr_keys;             //set which contains all legal pressed and not released keys;
    QVector <InfoWindow *> info_windows_v;
    const QPixmap          *bg_image;
    QBrush                 *footer_brush;
    QPolygon               footer_polygon;
    QTimer                 *fps_timer;
    QPointF                target;

    /*Custom elements:*/
    HpLine                 *hp_line;
    MiniMap                *mini_map;
    Weapon                 *weapon;
    Charger                *charger;
    InfoWindow             *info_window {nullptr};

    qreal                  hero_angle;
    QGraphicsView          *view;
    const int              wwidth;
    const int              wheight;
    const int              STEP {3};
};

#endif // GAMESCENE_H
