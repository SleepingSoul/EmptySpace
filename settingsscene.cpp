#include "settingsscene.h"

#include <QPainter>

SettingsScene::SettingsScene(const int w, const int h, QObject *parent)
    : QGraphicsScene(parent), wwidth(w), wheight(h)
{
    bg = new QPixmap  ("bg_settings.jpg");
}

SettingsScene::~SettingsScene()
{
    delete bg;
}

void SettingsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0, 0, wwidth, wheight, *bg);
    Q_UNUSED(rect);
}
