#ifndef UNITY_H
#define UNITY_H
#include <QtMath>

inline bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const qreal xdiff = point1.x() - point2.x();
    const qreal ydiff = point1.y() - point2.y();
    const qreal distance = qSqrt(xdiff * xdiff + ydiff * ydiff);

    if (distance <= radius1 + radius2)
        return true;

    return false;
}
#endif // UNITY_H
