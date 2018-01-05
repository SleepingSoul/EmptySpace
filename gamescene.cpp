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
#include "weapon.h"
#include "charger.h"
#include "infowindow.h"

GameScene::GameScene(const int w, const int h, const QPixmap *bg, QObject *parent)
    : QGraphicsScene(), wwidth(w), wheight(h), bg_image(bg)
{
    if (!bg)
        assert(false);

    readDecorations(QString("decor.txt"));

    foreach(Decoration *dec, dec_list) {
        this->addItem(dec);
    }

    hp_line = new HpLine();
    mini_map = new MiniMap();
    weapon = new Weapon();
    charger = new Charger();

    this->addItem(hp_line);
    this->addItem(mini_map);
    this->addItem(weapon);
    this->addItem(charger);

    fps_timer = new QTimer(this);
    connect(fps_timer, SIGNAL(timeout()), SLOT(slotUpdateViewport()));
    fps_timer->start(17);

    Q_UNUSED(parent);
}

GameScene::~GameScene()
{
    qDeleteAll(dec_list);
    delete charger;
    delete weapon;
    delete mini_map;
    delete hp_line;
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(-1000, -1000, *bg_image);

    /*Paint footer*/
    hp_line->setPos(rect.x() + rect.width() / 2. - 350, rect.y() + rect.height() - 30);
    mini_map->setHeroPos(phero->pos());
    mini_map->setPos(rect.x() + 10, rect.y() + rect.height() - 260);
    weapon->setPos(rect.x() + rect.width() - 200, rect.y() + rect.height() - 250);
    charger->setPos(rect.x() + 10, rect.y() + rect.height() - 460);

    size_t num = 0;
    foreach (auto info_w, info_windows_v) {
        info_w->setPos(rect.topRight() + QPointF(-info_w->Width() - 50, 50 + (num++ * info_w->Height() + 20)));
    }
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::setHero(Hero *h)
{
    phero = h;
    connect(phero, SIGNAL(signalHpChanged(int)), hp_line, SLOT(slotSetHeroHp(int)));
    connect(charger, SIGNAL(signalCharged()), phero, SLOT(slotCharged()));
    connect(phero, SIGNAL(signalCharged()), charger, SLOT(slotHeroCharged()));
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
    pr_keys.insert(static_cast <Qt::Key>(event->key()));

    if (static_cast <Qt::Key>(event->key()) == Qt::Key_E) {
        weapon->changeWeapon();
        phero->changeWeapon();
    }
    if (static_cast <Qt::Key>(event->key()) == Qt::Key_Shift) {
        phero->charge();
    }

    if (static_cast <Qt::Key>(event->key()) == Qt::Key_Q) {
        phero->activateShield();
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

void GameScene::addInfoWindow(InfoWindow *iw)
{
    info_windows_v.append(iw);
    this->addItem(iw);
}

void GameScene::popInfoWindow()
{
    if (!info_windows_v.empty())
        info_windows_v.removeFirst();
}
