#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QAbstractButton>

class CustomButton : public QAbstractButton
{
public:
    CustomButton();
    ~CustomButton();

private:
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // CUSTOMBUTTON_H
