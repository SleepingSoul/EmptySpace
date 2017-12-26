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
#include <QProgressBar>
#include <QGraphicsProxyWidget>
#include "hpline.h"
#include "minimap.h"

GameScene::GameScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(), wwidth(w), wheight(h)
{
    readDecorations(QString("decor.txt"));

    foreach(Decoration *dec, dec_list) {
        this->addItem(dec);
    }

    bg_image = new QPixmap("map_picture.jpg");

    hp_line = new HpLine();
    mini_map = new MiniMap();

    this->addItem(hp_line);
    this->addItem(mini_map);

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
    painter->drawPixmap(-1000, -1000, *bg_image);

    /*Paint footer*/
    hp_line->setPos(rect.x() + rect.width() / 2. - 350, rect.y() + rect.height() - 30);
    mini_map->setHeroPos(phero->pos());
    mini_map->setPos(rect.x() + 10, rect.y() + rect.height() - 260);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate();
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

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "press";
    emit signalShot(true);
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release";
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

void GameScene::setView(QGraphicsView *v)
{
    view = v;
}
