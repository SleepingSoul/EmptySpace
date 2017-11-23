#include "explosion.h"

Explosion::Explosion(QObject *parent)
    : QObject(parent)
{
    currentFrame = 0;       /// Координату X начала взрыва пули
    spriteImage = new QPixmap("sprite_sheet.png");

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
    connect(timer, SIGNAL(timeout()), SLOT(nextFrame()));
    timer->start(25);   /// Стартуем таймер с частотой 25 милисекунд
}

QRectF Explosion::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Отрисовываем один из кадров взрыва
    painter->drawPixmap(-10,-10, *spriteImage, currentFrame, 0, 20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Explosion::nextFrame()
{
    currentFrame += 20; // Продвигаем координату X для выбора следующего кадра
    if (currentFrame >= 300 )
        this->deleteLater();    // Если кадры закончились, то удаляем объект взрыва
}

int Explosion::type() const
{
    return Type;
}
