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
    QPainterPath path;
    QPolygon poly;
    poly.push_back(QPoint(50, 50));
    poly.push_back(QPoint(200, 200));
    poly.push_back(QPoint(50, 350));
    poly.push_back(QPoint(25, 75));
    path.addPolygon(poly);
    dec_vec.push_back(new Decoration(path));
    //</delete later>
    read_decorations(QString("decor.txt"));
    bg_image.load(":/bg_image_2.png");
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
    QPixmap cropped;
    QRect r(hor_offset, ver_offset, WIDTH, HEIGHT);
    cropped = bgimage.copy(r);

    painter->setPen(Qt::NoPen);
    painter->drawPixmap(0, 0, WIDTH, HEIGHT, cropped);

    //Creating a rect which contains our vision rect on global map
    QRect rscn(hor_offset, ver_offset, WIDTH, HEIGHT);

    //Removing all old items from scene
    for (auto dec_item : temp_decs)
        this->removeItem(dec_item);

    temp_decs.clear();

    for (Decoration *dec : dec_vec) {                               /*Here we are looking for all decorations
                                                                      which we should see on this part of global map*/
        if (dec->Path().intersects(rscn)) {                         /*If we found any decoration intersected with our
                                                                      vision rect, we cut the peace of this decoration
                                                                      and create new decoration as this peace, then
                                                                      we add it as an object to our scene*/
            QPainterPath rect_path;
            rect_path.addRect(rscn);
            QPainterPath is = dec->Path().intersected(rect_path);
            is.translate(-1 * hor_offset, -1 * ver_offset);
            Decoration *ndec = new Decoration(is);                  /*Creating new decoration and saving it in vector
                                                                      to delete later*/
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

void CustomScene::set_background(QPixmap pm)
{
    bg_image = pm;
}

void CustomScene::read_decorations(QString fileName)
{
    QFile dec_file(":/decor.txt");
    if (dec_file.isOpen())
        qDebug() << "file is open!";
    if (dec_file.exists())
        qDebug() << "file exists!";
    if (dec_file.open(QIODevice::ReadOnly)) {
        QTextStream tstream(&dec_file);
        QString str;
        while (!tstream.atEnd()) {
            str = tstream.readLine();
            qDebug() << str;
        }
    }
    else {
        qDebug() << "No decorations file!";
    }
}
