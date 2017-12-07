#include "menuscene.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

MenuScene::MenuScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(parent),
      WIDTH(w),
      HEIGHT(h)
{
    logo = new QPixmap("emptyspace_logo.png");
    bg = new QPixmap  ("menu_bg.jpg");
    opacity_timer = new QTimer(this);
    connect(opacity_timer, SIGNAL(timeout()), SLOT(slotChangeOpacity()));
    opacity_timer->start(30);
}

MenuScene::~MenuScene()
{
    delete logo;
    delete bg;
    qDebug() << "Menu scene destr";
}

void MenuScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0, 0, WIDTH, HEIGHT, *bg);
    painter->setOpacity(opacity / 100);
    painter->drawPixmap(30, -20, *logo);
    Q_UNUSED(rect);
}

void MenuScene::slotChangeOpacity()
{
    static bool direction(true);
    if (direction) {
        --opacity;
        if (opacity <= 0)
            direction = false;
    }
    else {
        ++opacity;
        if (opacity >= 100)
            direction = true;
    }
    this->update(logo->rect());
}