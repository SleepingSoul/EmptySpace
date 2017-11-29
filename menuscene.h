#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(const int w, const int h, QObject *parent = 0);
    ~MenuScene();

private:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    QPixmap *bg;
    QPixmap *logo;
    const int WIDTH;
    const int HEIGHT;
};

#endif // MENUSCENE_H
