#include "customtextitem.h"
#include <QPainter>
#include <QDebug>
#include <QDateTime>

CustomTextItem::CustomTextItem()
{
    font.setFamily("Lucida Console");
}

CustomTextItem::~CustomTextItem()
{

}

void CustomTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    font.setPointSize(30);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
//    painter->drawText(0, 0, this->text().left(2));
    painter->setOpacity(opacity / 100.);

//    painter->drawText(55, 0, ":");
//    painter->setOpacity(1);
    painter->drawText(0, 0, QDateTime::currentDateTime().time().toString().left(5));
    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(70, 30, QDateTime::currentDateTime().date().toString("ddd.dd"));

    changeOpacity();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CustomTextItem::changeOpacity()
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
}
