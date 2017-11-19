#include "customscene.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static const double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    //function makes angle from 0 to TwoPi
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

CustomScene::CustomScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(),
      hor_offset(0),
      ver_offset(0),
      phero(nullptr),
      phthrust(nullptr),
      STEP(3),
      WIDTH(w),
      HEIGHT(h),
      robot_angle(0)
{
    read_decorations(QString("decor.txt"));

    foreach(Decoration *dec, dec_vec) {
        this->addItem(dec);
        dec->set_def_pos(dec->pos().toPoint());
    }

    bg_image.load("galaxy_map10kx10k.jpg");

    fps_timer = new QTimer(this);
    connect(fps_timer, SIGNAL(timeout()), SLOT(slotFPStimer()));
    fps_timer->start(18);
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{
    foreach(Decoration *dec, dec_vec) {
        this->removeItem(dec);
    }
    foreach (auto x, dec_vec)
        delete x;
}

void CustomScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPixmap cropped;
    QRect rscn(hor_offset, ver_offset, WIDTH, HEIGHT);
    cropped = bg_image.copy(rscn);

    if (offsets_changed) {

        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);
        painter->setBrush(QBrush(Qt::darkGray));

        foreach (Decoration *dec, dec_vec)                              /*we are moving all decorations depending
                                                                          on offsets*/
            dec->setPos(-1 * dec->def_pos().x() - hor_offset, -1 * dec->def_pos().y() - ver_offset);
        offsets_changed = false;
    }
    else
        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);
    Q_UNUSED(rect);
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    targetCoordinate(event->scenePos());
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W ||
        event->key() == Qt::Key_A ||
        event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D)
        pr_keys.insert(Qt::Key(event->key()));
}

void CustomScene::keyReleaseEvent(QKeyEvent *event)
{
    pr_keys.remove(Qt::Key(event->key()));
}

void CustomScene::set_hero(Hero *h)
{
    phero = h;
}

void CustomScene::set_background(const QPixmap pm)
{
    bg_image = pm;
}

void CustomScene::read_decorations(const QString fileName)
{
    QFile dec_file(fileName);

    if (dec_file.open(QIODevice::ReadOnly)) {
        QTextStream tstream(&dec_file);
        QString str;

        while (!tstream.atEnd()) {
            str = tstream.readLine();

            if (str.startsWith("//"))
                continue;
            qDebug() << str;
            QPolygon poly;
            QStringList lst = str.split(' ', QString::SkipEmptyParts);

            if (lst.size() % 2 != 0) {
                qDebug() << "Wrong coords string! Reading of string <" << str << "> failed!";
                continue;
            }

            for (auto s_it = lst.cbegin(); s_it != lst.cend(); s_it += 2) {
                poly.push_back(QPoint((*s_it).toInt(), (*(s_it + 1)).toInt()));             //!can be dangerous!
            }
            dec_vec.push_back(new Decoration(poly));
        }
    }
    else {
        qDebug() << "No decorations file!";
    }
}

void CustomScene::slotChangeOffsetChangedFlag(bool f)
{
    offsets_changed = f;
}

void CustomScene::slotFPStimer()
{
    dir result_dir = NO_DIR;

    if (pr_keys.contains(Qt::Key_W)) {
        move_hero_y(phero->y() - STEP);
        if (this->collidingItems(phero).size() != 1)
            move_hero_y(phero->y() + STEP);

        emit transfer_HeroMovingState_to_HeroThrust(true);

        result_dir = N;
    }

    if (pr_keys.contains(Qt::Key_A)) {
        move_hero_x(phero->x() - STEP);
        if (this->collidingItems(phero).size() != 1)
            move_hero_x(phero->x() + STEP);

        emit transfer_HeroMovingState_to_HeroThrust(true);

        if (result_dir == N) result_dir = NW;
        else                 result_dir = W;
    }

    if (pr_keys.contains(Qt::Key_S)) {
        move_hero_y(phero->y() + STEP);
        if (this->collidingItems(phero).size() != 1)
            move_hero_y(phero->y() - STEP);

        emit transfer_HeroMovingState_to_HeroThrust(true);

        if (result_dir == W) result_dir = SW;
        else                 result_dir = S;
    }

    if (pr_keys.contains(Qt::Key_D)) {
        move_hero_x(phero->x() + STEP);
        if (this->collidingItems(phero).size() != 1)
            move_hero_x(phero->x() - STEP);

        emit transfer_HeroMovingState_to_HeroThrust(true);

        if      (result_dir == N) result_dir = NE;
        else if (result_dir == S) result_dir = SE;
        else                      result_dir = E;
    }

    if (!pr_keys.isEmpty())                                         //we check out set to be not empty
        emit transfer_HeroDirecion_to_HeroThrust(result_dir);       /*because if no buttons are pressed,
                                                                      we should use previous direction
                                                                      for painting faiding of thrusts*/

    if (phero->x() - 200 < 0) {
        moveBackground(W);
        move_hero_x(200);
    }
    if (phero->x() + 200 > 1000) {
        moveBackground(E);
        move_hero_x(800);
    }
    if (phero->y() - 200 < 0) {
        moveBackground(N);
        move_hero_y(200);
    }
    if(phero->y() + 200 > 600) {
        moveBackground(S);
        move_hero_y(400);
    }
    QLineF lineToTarget(phero->pos(), target);
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    robot_angle = -1 * qRadiansToDegrees(angleToTarget);
    phero->setRotation(robot_angle);
    this->update();
}

void CustomScene::targetCoordinate(QPointF point)
{
    //Rotate hero straight to cursor target
    target = point;
}

void CustomScene::moveBackground(const dir d)
{
    switch (d) {
    case W:
        hor_offset -= STEP;
        break;
    case E:
        hor_offset += STEP;
        break;
    case N:
        ver_offset -= STEP;
        break;
    case S:
        ver_offset += STEP;
        break;
    default:
        assert(false);
    }
    offsets_changed = true;
}

void CustomScene::set_hero_thrust(HeroThrust *ht)
{
    phthrust = ht;
}

void CustomScene::move_hero_x(const int x)
{
    phero->setX(x);
    phthrust->setX(x);
}

void CustomScene::move_hero_y(const int y)
{
    phero->setY(y);
    phthrust->setY(y);
}
