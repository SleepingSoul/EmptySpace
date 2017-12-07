#include "gamescene.h"
#include "project_math.h"

GameScene::GameScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(), wwidth(w), wheight(h)
{
    readDecorations(QString("decor.txt"));

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

GameScene::~GameScene()
{
    foreach(Decoration *dec, dec_vec) {
        this->removeItem(dec);
        delete dec;
    }
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0, 0, bg_image);
    Q_UNUSED(rect);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::setHero(Hero *h)
{
    phero = h;
}

void GameScene::readDecorations(const QString fileName)
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

void GameScene::slotUpdateViewport()
{
    this->update();
}

void GameScene::targetCoordinate(QPointF point)
{
    //Rotate hero straight to cursor target
    target = point;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true);
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false);
    QGraphicsScene::mouseReleaseEvent(event);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if ((static_cast <Qt::Key>(event->key()) == Qt::Key_W ||
        static_cast <Qt::Key>(event->key()) == Qt::Key_A ||
        static_cast <Qt::Key>(event->key()) == Qt::Key_S ||
        static_cast <Qt::Key>(event->key()) == Qt::Key_D) &&
        pr_keys.size() < 2)
    {
        pr_keys.insert(static_cast <Qt::Key>(event->key()));
    }
    emit signalButtons(pr_keys);
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    pr_keys.remove(static_cast <Qt::Key>(event->key()));
    emit signalButtons(pr_keys);
    QGraphicsScene::keyReleaseEvent(event);
}
