#include "aboutscene.h"
#include <QPainter>

AboutScene::AboutScene(const int w, const int h, QObject *parent)
    : width(w), height(h), QGraphicsScene()
{
    this->setSceneRect(0, 0, width, height);
    bg = new QPixmap("bg_settings.jpg");
    Q_UNUSED(parent);
}

AboutScene::~AboutScene()
{
    delete bg;
}

void AboutScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0, 0, width, height, *bg);
    Q_UNUSED(rect);
}
