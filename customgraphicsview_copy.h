#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomGraphicsView(QWidget *parent = 0);

    //void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // CUSTOMGRAPHICSVIEW_H
