#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QGraphicsScene>

class SettingsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SettingsScene(const int w, const int h, QObject *parent = 0);
    ~SettingsScene();

private:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    QPixmap *bg;
    const int wwidth;
    const int wheight;
};

#endif // SETTINGSSCENE_H
