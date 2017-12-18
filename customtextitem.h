#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include <QGraphicsSimpleTextItem>
#include <QFont>

class QTimer;

class CustomTextItem : public QGraphicsSimpleTextItem
{
public:
    CustomTextItem();
    ~CustomTextItem();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QFont font;
    int opacity {0};
    bool flag {false};
    inline void changeOpacity();
};

#endif // CUSTOMTEXTITEM_H
