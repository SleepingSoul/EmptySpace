#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>

class QTimer;

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(const int w, const int h, QObject *parent = 0);
    ~MenuScene();
    void setBackgroundImage(const int);

private:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    QPixmap *bg;
    QPixmap *logo;
    const int WIDTH;
    const int HEIGHT;

    QTimer *opacity_timer;
    qreal opacity {100};

private slots:
    void slotChangeOpacity();
};

#endif // MENUSCENE_H
