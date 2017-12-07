#ifndef ABOUTSCENE_H
#define ABOUTSCENE_H

#include <QGraphicsScene>

class AboutScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AboutScene(const int w, const int h, QObject *parent = 0);
    ~AboutScene();

private:
    void drawBackground(QPainter *, const QRectF &) override;
    QPixmap   *bg;
    const int width;
    const int height;
};

#endif // ABOUTSCENE_H
