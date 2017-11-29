#include "menuscene.h"
#include <QPainter>
#include <QDebug>

MenuScene::MenuScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(parent),
      WIDTH(w),
      HEIGHT(h)
{
    logo = new QPixmap("emptyspace_logo.png");
    bg = new QPixmap  ("menu_bg.jpg");
}

MenuScene::~MenuScene()
{
    delete logo;
    delete bg;
}

void MenuScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0, 0, WIDTH, HEIGHT, *bg);
    painter->drawPixmap(100, 0, *logo);
    Q_UNUSED(rect);
}
