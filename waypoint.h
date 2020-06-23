#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <QPoint>
class QPainter;

class Waypoint
{
public:
    Waypoint(QPoint pos);
    void setnext(Waypoint *nextpoint);
    Waypoint* nextWaypoint() const;
    const QPoint pos() const;
    void draw(QPainter *painter) const;
private:
    QPoint my_pos;
    Waypoint * my_nextwaypoint;
};

#endif // WAYPOINT_H
