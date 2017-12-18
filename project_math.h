#ifndef PROJECT_MATH_H
#define PROJECT_MATH_H

#include <QtMath>

static const double Pi = 3.14159265358979323846264338327950288419717;
static const double TwoPi = 2. * Pi;

static qreal normalizeRadians(qreal angle)
{
    //function makes angle from 0 to TwoPi
    while (angle < 0)     angle += TwoPi;
    while (angle > TwoPi) angle -= TwoPi;
    return angle;
}

static qreal normalizeDegrees(qreal angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
    return angle;
}

#endif // PROJECT_MATH_H
