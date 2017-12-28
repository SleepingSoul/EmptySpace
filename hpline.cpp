#include "hpline.h"
#include <QPainter>
#include <QDebug>

HpLine::HpLine(QObject *parent)
    : QObject(parent)
{
    this->setZValue(4);
}

HpLine::~HpLine()
{

}

QRectF HpLine::boundingRect() const
{
    return QRectF(0, 0, 500, 50);
}

void HpLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(QColor(11, 48, 15)));
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(106, 212, 186));
    //painter->setPen(pen);
    painter->drawRect(0, 0, 700 * hero_hp / 1000, 20);
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(700 * hero_hp / 1000, 0, 700 - 700 * hero_hp / 1000, 20);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, 700, 20);
    QFont font;
    font.setPointSize(7);
    painter->setFont(font);
    painter->drawText(345, 14, "HP");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void HpLine::slotSetHeroHp(const int hp)
{
    hero_hp = hp;
}

int HpLine::type() const
{
    return SimpleType;
}
