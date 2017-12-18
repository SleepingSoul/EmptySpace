#ifndef TEMPLATES_H
#define TEMPLATES_H

class QPushButton;
class QRegion;
class QPoint;
class QIcon;
class QPixmap;

#include <QPushButton>

//Definition of some user-case constants
#define CHANGE_T_MS 250 /*time before state change*/

/* Tempate function, that sets up standart designed button of this
 *program. Params:
 *pbtn - QPushButton pointer;
 *icon_name - string with adress of picture */

static void setUpButton(QPushButton *pbtn, const char *icon_name)
{
    //sets up clear button to required form with icon
    static QRegion reg(QPolygon() << QPoint(0,10) << QPoint(10, 0) << QPoint(240, 0) << QPoint(240, 42.12) <<
                       QPoint(230, 52.12) << QPoint(0, 52.12));
    pbtn->setIcon(QIcon(QPixmap(icon_name)));
    pbtn->setIconSize(QSize(240, 52.12));
    pbtn->setFixedSize(240, 52.12);
    pbtn->setMask(reg);
    pbtn->setStyleSheet("QPushButton:hover {"
                            "border: 1px;"
                            "background: lightblue;"
                        "}");
}

#endif // TEMPLATES_H
