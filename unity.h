#ifndef UNITY_H
#define UNITY_H
#include <QtMath>

inline bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const qreal xdif = point1.x() - point2.x();
    const qreal ydif = point1.y() - point2.y();
    const qreal distance = qSqrt(xdif * xdif + ydif * ydif);

    if (distance <= radius1 + radius2)
        return true;

    return false;
}
#endif // UNITY_H
