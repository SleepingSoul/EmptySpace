#include "customscene.h"
#include "project_math.h"

CustomScene::CustomScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(),
      WIDTH(w),
      HEIGHT(h)
{
    read_decorations(QString("decor.txt"));

    foreach(Decoration *dec, dec_vec) {
        this->addItem(dec);
        dec->set_def_pos(dec->pos().toPoint());
    }

    bg_image.load("galaxy_map10kx10k.jpg");

    fps_timer = new QTimer(this);
    connect(fps_timer, SIGNAL(timeout()), SLOT(slotUpdateViewport()));
    fps_timer->start(18);

    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{
    foreach(Decoration *dec, dec_vec) {
        this->removeItem(dec);
        delete dec;
    }
}

void CustomScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    //qDebug() << offsets_changed;
    QPixmap cropped;
    QRect rscn(hor_offset, ver_offset, WIDTH, HEIGHT);
    cropped = bg_image.copy(rscn);

    if (offsets_changed) {

        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);
        painter->setBrush(QBrush(Qt::darkGray));

        foreach (QGraphicsItem *item, this->items(this->sceneRect())) { //требуется доработка!!!
            if (item != phero && item->zValue() != 5) {
                switch (offsets_dir) {
                case N:
                    item->setY(item->y() + STEP);
                    break;
                case S:
                    item->setY(item->y() - STEP);
                    break;
                case W:
                    item->setX(item->x() + STEP);
                    break;
                case E:
                    item->setX(item->x() - STEP);
                    qDebug() << "to " << item->x();
                    break;
                case NW:
                    item->setY(item->y() + STEP);
                    item->setX(item->x() + STEP);
                    break;
                case NE:
                    item->setY(item->y() + STEP);
                    item->setX(item->x() - STEP);
                    break;
                case SW:
                    item->setY(item->y() - STEP);
                    item->setX(item->x() + STEP);
                    break;
                case SE:
                    item->setY(item->y() - STEP);
                    item->setX(item->x() - STEP);
                    break;
                }
            }
        }

        foreach (Decoration *dec, dec_vec)                              /*we are moving all decorations depending
                                                                          on offsets*/
            dec->setPos(-1 * dec->def_pos().x() - hor_offset, -1 * dec->def_pos().y() - ver_offset);
        offsets_changed = false;
    }
    else
        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);
    offsets_changed = false;
    Q_UNUSED(rect);
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
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

            QStringList lst = str.split(' ', QString::SkipEmptyParts);

            if (lst.size() % 2 != 0) {
                qDebug() << "Wrong coords string! Reading of string <" << str << "> failed!";
                continue;
            }

            QPolygon poly;

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

void CustomScene::slotUpdateViewport()
{
    this->update();
}

void CustomScene::targetCoordinate(QPointF point)
{
    //Rotate hero straight to cursor target
    target = point;
}

void CustomScene::slotMoveBackground(dir d)
{
    offsets_dir = d;

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
    case NW:
        ver_offset -= STEP;
        hor_offset -= STEP;
        break;
    case NE:
        ver_offset -= STEP;
        hor_offset += STEP;
        break;
    case SW:
        ver_offset += STEP;
        hor_offset -= STEP;
        break;
    case SE:
        ver_offset += STEP;
        hor_offset += STEP;
        break;
    default:
        assert(false);
    }

    offsets_changed = true;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true);
    QGraphicsScene::mousePressEvent(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false);
    QGraphicsScene::mouseReleaseEvent(event);
}
