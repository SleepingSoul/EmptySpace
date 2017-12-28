#ifndef HPLINE_H
#define HPLINE_H

#include "gameplayitem.h"
#include <QObject>

class HpLine : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit HpLine(QObject *parent = 0);
    ~HpLine();

    int type() const override;

    void stopTime() override {}
    void startTime() override {}

public slots:
    void slotSetHeroHp(int);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    int hero_hp {1000};
};

#endif // HPLINE_H
