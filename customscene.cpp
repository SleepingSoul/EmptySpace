#include "customscene.h"

CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(),
      hor_offset(0),
      ver_offset(0),
      phero(nullptr)
{
    //<delete later>
    srand(0);
    for (int i = 0; i < 25; ++i) {
        dec_vec.push_back(new Decoration(QRect(rand() % 2000, rand() % 1200, rand() % 300, rand() % 300)));
    }
    //</delete later>
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{
    for (auto x : dec_vec)
        delete x;
}

/*<params>
 * painter : painter of this scene;
 * rect : rect there it's nesessary to repaint the background at this case;
 * </params>
*/
void CustomScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPixmap bg, cropped;
    QRect r(hor_offset, ver_offset, 1000, 600);
    bg.load(":/bg_image_1.png");
    cropped = bg.copy(r);

    painter->setPen(Qt::NoPen);
    painter->drawPixmap(0, 0, 1000, 600, cropped);

    //drawing decorations
    QRect rscn(hor_offset, ver_offset, 1000, 600);

    for (auto dec_item : temp_decs)
        this->removeItem(dec_item);
    temp_decs.clear();
    for (Decoration *dec : dec_vec) {
        if (rscn.intersects(dec->Rect())) {
            QRect is = rscn.intersected(dec->Rect());
            Decoration *ndec = new Decoration(QRect(is.x() - hor_offset, is.y() - ver_offset, is.width(), is.height()));
            temp_decs.push_back(ndec);
            this->addItem(ndec);
        }
    }

    this->update();
    Q_UNUSED(rect);
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void CustomScene::slotMoveBackground(dir d)
{
    switch(d) {
    case LEFT:
        hor_offset -= 1;
        break;
    case RIGHT:
        hor_offset += 1;
        break;
    case TOP:
        ver_offset -= 1;
        break;
    case BOT:
        ver_offset += 1;
        break;
    default:
        assert(false);
    }
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    //todo
    Q_UNUSED(event);
}

void CustomScene::set_hero_coords(const int x, const int y)
{
    //todo
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
