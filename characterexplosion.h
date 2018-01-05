#ifndef CHARACTEREXPLOSION_H
#define CHARACTEREXPLOSION_H

#include "explosion.h"
#include <QMediaPlayer>

class CharacterExplosion : public Explosion
{
    Q_OBJECT
public:
    explicit CharacterExplosion(QObject *parent = 0);
    ~CharacterExplosion();

private:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
    QMediaPlayer *player;

private slots:
    void nextFrame() override;
    void slotMediaStateChanged(QMediaPlayer::State);
};

#endif // CHARACTEREXPLOSION_H
