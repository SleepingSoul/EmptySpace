#include "hero.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    //function makes angle from 0 to TwoPi
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Hero::Hero(QObject *parent) :
    QObject(parent),
    QGraphicsItem()
{
    setRotation(0);                     //first rotation of the hero always 0

    target = QPointF(0, 0);             //first direction of hero - NW

    //Set up timer
    gameTimer = new QTimer();
    connect(gameTimer, SIGNAL(timeout()), SLOT(slotGameTimer()));
    gameTimer->start(5);   // Стартуем таймеp
}

Hero::~Hero()
{

}

QRectF Hero::boundingRect() const
{
    //bounding rect of hero
    return QRectF(-10, -10, 20, 20);
}

QPainterPath Hero::shape() const
{
    //Shape of hero (ellipse in this case)
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Paint hero (triangle in this case)
    QPolygon polygon;
    polygon << QPoint(0,-15) << QPoint(12,15) << QPoint(-12,15);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Hero::slotTarget(QPointF point)
{
    //Find distance to target
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Hero::slotGameTimer()
{
    // Перемещаем треугольник в зависимости от нажатых кнопок
    bool fl = !scene()->collidingItems(this).isEmpty();
    if(GetAsyncKeyState('A')) {
        this->setX(this->x() - 1);
        //Collision checking x4
        if(!scene()->collidingItems(this).isEmpty()) {
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState('D')) {
        this->setX(this->x() + 1);
        if(!scene()->collidingItems(this).isEmpty()) {
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState('W')) {
        this->setY(this->y() - 1);
        if(!scene()->collidingItems(this).isEmpty()) {
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState('S')) {
        this->setY(this->y() + 1);
        if(!scene()->collidingItems(this).isEmpty()) {
            this->setY(this->y() - 1);
        }
    }

    if(this->x() - 200 < 0) {
        emit moveBackground(LEFT);
        this->setX(200);
    }
    if(this->x() + 200 > 1000) {
        emit moveBackground(RIGHT);
        this->setX(800);
    }
    if(this->y() - 200 < 0) {
        emit moveBackground(TOP);
        this->setY(200);
    }
    if(this->y() + 200 > 600) {
        emit moveBackground(BOT);
        this->setY(400);
    }

    slotTarget(target);                                     //update the rotation
}
