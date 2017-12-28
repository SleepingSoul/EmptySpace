#include "characterexplosion.h"
#include <QTimer>
#include <QPixmap>
#include <QPainter>

CharacterExplosion::CharacterExplosion(QObject *parent)
{
    currentFrame = 0;
    spriteImage = new QPixmap("big_sprite_sheet.png");

    player = new QMediaPlayer;
    player->setMedia((QMediaContent(QUrl::fromLocalFile("Explosion.wav"))));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(nextFrame()));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotMediaStateChanged(QMediaPlayer::State)));
    timer->start(18);
    player->play();
}

CharacterExplosion::~CharacterExplosion()
{
    delete player;
}

QRectF CharacterExplosion::boundingRect() const
{
    return QRectF(-100,-100,200,200);
}

void CharacterExplosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Отрисовываем один из кадров взрыва
    painter->drawPixmap(-100,-100, *spriteImage, currentFrame, 0, 200, 200);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CharacterExplosion::nextFrame()
{
    if (currentFrame < 3000)
        currentFrame += 200;
}

void CharacterExplosion::slotMediaStateChanged(QMediaPlayer::State st)
{
    if (st == QMediaPlayer::StoppedState) {
        this->deleteLater();
    }
}
