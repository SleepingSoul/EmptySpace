#ifndef WEAPON_H
#define WEAPON_H

#include "gameplayitem.h"
#include <QObject>
#include "global_enumerations.h"

class QTimer;

class Weapon : public QObject, public GameplayItem
{
    Q_OBJECT
public:
    explicit Weapon(QObject * = 0);
    ~Weapon();

    void stopTime() override;
    void startTime() override;
    int type() const override;

    void changeWeapon();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    WeaponOptions::WeaponType current_weapon {WeaponOptions::Blaster};
    QPixmap weapon_image;
    QPixmap bg_image;
    unsigned short offset {0};
    bool _was_changed{false};
    QTimer *timer;

private slots:
    void slotChangeOffset();
};

#endif // WEAPON_H
