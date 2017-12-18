#include "gamescene.h"
#include "project_math.h"
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <cassert>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>
#include "decoration.h"
#include "hero.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsView>

GameScene::GameScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(), wwidth(w), wheight(h)
{
    readDecorations(QString("decor.txt"));

    foreach(Decoration *dec, dec_list) {
        this->addItem(dec);
    }

    bg_image = new QPixmap("map_picture.jpg");

    fps_timer = new QTimer(this);
    connect(fps_timer, SIGNAL(timeout()), SLOT(slotUpdateViewport()));
    fps_timer->start(17);

    Q_UNUSED(parent);
}

GameScene::~GameScene()
{
    qDeleteAll(dec_list);
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    /*Maybe we could optimise it*/
    //painter->drawPixmap(rect.toRect(), bg_image->copy(rect.x() + 500, rect.y() + 500, rect.width(), rect.height()));
    painter->drawPixmap(-500, -500, *bg_image);
    //have no idea why, but second variant is a little bit FASTER than 1.
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

            if (str.startsWith("//"))   /*commentary string*/
                continue;

            QStringList lst = str.split(' ', QString::SkipEmptyParts);

            if (lst.size() % 2 != 0) {
                /*Maybe, we should make exception here*/
                qDebug() << "Wrong coords string! Reading of string <" << str << "> failed!";
                continue;
            }

            QPolygon poly;

            for (auto s_it = lst.cbegin(); s_it != lst.cend(); s_it += 2) {
                poly.push_back(QPoint((*s_it).toInt(), (*(s_it + 1)).toInt()));
            }

            dec_list.push_back(new Decoration(poly));
        }
    }
    else {
        /*Maybe. we should throw exception here*/
        qDebug() << "No decorations file!";
    }
}

void GameScene::slotUpdateViewport()
{
    this->update();
}

void GameScene::targetCoordinate(QPointF point)
{
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
