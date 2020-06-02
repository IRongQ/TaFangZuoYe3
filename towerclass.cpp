#include "towerclass.h"
#include <QPainter>
#include <QPoint>
#include <QPixmap>

Towerclass::Towerclass(QPoint pos, QString style_filename) : QObject(0),pixmap(style_filename)
{
    position = pos;
}
void Towerclass::draw(QPainter *painter){
    painter->drawPixmap(position,pixmap);
}
