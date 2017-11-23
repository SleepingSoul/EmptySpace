#include "hero.h"
#include "project_math.h"

Hero::Hero(QObject *parent) :

    QObject       (parent),
    QGraphicsItem ()
{
    setRotation(0);
    hero_pic = new QPixmap("spaceship_pic150x150.png");
    bulletPic = new QPixmap("bullet_1.png");
    ptimer = new QTimer(this);
    pshoting_timer = new QTimer(this);

    connect(ptimer, SIGNAL(timeout()), SLOT(slotHeroTimer()));
    connect(ptimer, SIGNAL(timeout()), SLOT(slotTwirl()));
    connect(pshoting_timer, SIGNAL(timeout()), SLOT(slotShoting()));
}

Hero::~Hero()
{
    delete hero_pic;
    delete bulletPic;
}

QRectF Hero::boundingRect() const
{
    //bounding rect of hero
    return QRectF(-30, -30, 60, 60);
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
    painter->drawPixmap(-50, -50, 100, 100, *hero_pic);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Hero::slotHeroTimer()
{
    pthrust->setPos(this->pos());

    dir direction(NO_DIR);

    //pthrust->pos() = this->pos();

    if(GetAsyncKeyState('A')) {
        this->setX(this->x() - STEP);
        pthrust->setX(pthrust->x() - STEP);

        if(scene()->collidingItems(this).size() != 1){
            this->setX(this->x() + STEP);
            pthrust->setX(pthrust->x() + STEP);
        }
        pthrust->setMoving(true);
        direction = W;
    }

    if(GetAsyncKeyState('D')) {
        this->setX(this->x() + STEP);
        pthrust->setX(pthrust->x() + STEP);

        if(scene()->collidingItems(this).size() != 1){
            this->setX(this->x() - STEP);
            pthrust->setX(pthrust->x() - STEP);
        }
        pthrust->setMoving(true);
        if (direction != W) direction = E;
    }

    if(GetAsyncKeyState('W')) {
        this->setY(this->y() - STEP);
        pthrust->setY(pthrust->y() - STEP);

        if(scene()->collidingItems(this).size() != 1){
            this->setY(this->y() + STEP);
            this->setY(this->y() + STEP);
        }
        pthrust->setMoving(true);
        if (direction == W) direction = NW;
        else if (direction == E) direction = NE;
        else direction = N;
    }

    if(GetAsyncKeyState('S')) {
        this->setY(this->y() + STEP);
        pthrust->setY(pthrust->y() + STEP);

        if(scene()->collidingItems(this).size() != 1){
            this->setY(this->y() - STEP);
            pthrust->setY(pthrust->y() - STEP);
        }
        pthrust->setMoving(true);
        if (direction == W) direction = SW;
        else if (direction == E) direction = SE;
        else direction = S;
    }

    pthrust->setDirection(direction);

    dir d(NO_DIR);

    if (x() - 200 < 0) {
        setX(x() + STEP);
        pthrust->setX(pthrust->x() + STEP);
        d = W;
    }

    if (x() + 200 > 1000) {
        setX(x() - STEP);
        pthrust->setX(pthrust->x() - STEP);
        d = E;
    }

    if (y() - 200 < 0) {
        setY(y() + STEP);
        pthrust->setY(pthrust->y() + STEP);
        if (d == W)
            d = NW;
        else if (d == E)
            d = NE;
        else d = N;
    }

    if (y() + 200 > 600) {
        setY(y() - STEP);
        pthrust->setY(pthrust->y() - STEP);
        if (d == W) d = SW;
        else if (d == E) d = SE;
        else d = S;
    }
    if (d != NO_DIR)
        emit moveBackground(d);
}

void Hero::slotTwirl()
{
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;

    angleToTarget = normalizeRadians((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi)
        // Rotate left
        setRotation(rotation() - qMin(angleToTarget * 180 /Pi, 4.0));
    else if (angleToTarget <= TwoPi && angleToTarget > Pi)
        // Rotate right
        setRotation(rotation() + qMin((angleToTarget - TwoPi )* (-180) /Pi, 4.0));
}

void Hero::slotTarget(QPointF point)
{
    target = point;
}

QVariant Hero::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSceneChange && value.value <QGraphicsScene *>()) {    //value = scene ptr
        pthrust = new HeroThrust;
        pthrust->setZValue(0);
        pthrust->setPos(this->pos());
        value.value <QGraphicsScene *>()->addItem(pthrust);

        ptimer->start(17);
    }
    return QGraphicsItem::itemChange(change, value);
}

void Hero::slotShoting()
{
    Bullet *bullet = new Bullet(25, bulletPic);
    bullet->setPos(mapToParent(0, -100));
    bullet->setRotation(this->rotation());
    bullet->setZValue(1);
    scene()->addItem(bullet);
    qDebug() << "scene items size: " << scene()->items().size();
}

void Hero::slotShot(bool f)
{
    if (f) pshoting_timer->start(shot_interval);
    else pshoting_timer->stop();
}
