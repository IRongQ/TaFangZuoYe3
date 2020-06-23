#include "waypoint.h"
#include <QPainter>
#include <QColor>

Waypoint::Waypoint(QPoint pos):my_pos(pos),my_nextwaypoint(NULL){}

void Waypoint::setnext(Waypoint *nextpoint){
    my_nextwaypoint = nextpoint;
}

Waypoint* Waypoint::nextWaypoint() const{
    return my_nextwaypoint;
}

const QPoint Waypoint::pos() const{
    return my_pos;
}

void Waypoint::draw(QPainter *painter) const{
    painter->save();
    painter->setPen(QColor(0,255,0));
    painter->drawEllipse(my_pos,6,6);
    painter->drawEllipse(my_pos,2,2);

    if(my_nextwaypoint)
        painter->drawLine(my_pos,my_nextwaypoint->my_pos);
    painter->restore();
}
