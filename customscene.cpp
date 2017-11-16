#include "customscene.h"

CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(),
      hor_offset(0),
      ver_offset(0),
      phero(nullptr)
{
    read_decorations(QString("decor.txt"));
    bg_image.load(":/bg_image_1.png");
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{
    foreach (auto x, dec_vec)
        delete x;
}

/*<params>
 * painter : painter of this scene;
 * rect : rect there it's nesessary to repaint the background in this case;
 * </params>
*/
void CustomScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (offsets_changed) {
        QPixmap cropped;
        QRect rscn(hor_offset, ver_offset, WIDTH, HEIGHT);
        cropped = bg_image.copy(rscn);

        painter->setPen(Qt::NoPen);
        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);

        QPolygon poly(rscn);

        //Removing all old items from scene
        foreach (auto dec_item, temp_decs) {
            this->removeItem(dec_item);
            delete dec_item;
        }

        temp_decs.clear();

        foreach (Decoration *dec, dec_vec) {                         /*Here we are looking for all decorations
                                                                      which we should see on this part of global map*/
            QPolygon is = poly.intersected(dec->Polygon());
            if (!is.isEmpty()) {                                     /*If we found any decoration intersected with our
                                                                      vision rect, we cut the peace of this decoration
                                                                      and create new decoration as this peace, then
                                                                      we add it as an object to our scene*/
                is.translate(-1 * hor_offset, -1 * ver_offset);
                Decoration *ndec = new Decoration(is);               /*Creating new decoration and saving it in vector
                                                                      to delete later*/
                temp_decs.push_back(ndec);
                this->addItem(ndec);
            }
        }
        this->update(rect.toRect());        //!!!!!!!!!!!!!
    }
    else {
        QPixmap cropped;
        QRect rscn(hor_offset, ver_offset, WIDTH, HEIGHT);
        cropped = bg_image.copy(rscn);

        painter->setPen(Qt::NoPen);
        painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);
    }
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void CustomScene::slotMoveBackground(dir d)
{
    switch(d) {
    case LEFT:
        --hor_offset;
        break;
    case RIGHT:
        ++hor_offset;
        break;
    case TOP:
        --ver_offset;
        break;
    case BOT:
        ++ver_offset;
        break;
    default:
        assert(false);
    }
    offsets_changed = true;
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    //todo
    Q_UNUSED(event);
}

void CustomScene::set_hero(Hero *h)
{
    phero = h;
}

void CustomScene::set_size(const int w, const int h)
{
    WIDTH = w;
    HEIGHT = h;
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
                qDebug() << "Wrong coords string! Reading of string " << str << "failed!";
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
