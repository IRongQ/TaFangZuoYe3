#ifndef TOWERCLASS_H
#define TOWERCLASS_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Towerclass : public QObject
{
    Q_OBJECT
public:
    Towerclass(QPoint pos, QString style_filename );
    void draw(QPainter * painter);

signals:

private:
    QPoint position;
    QPixmap pixmap;
};

#endif // TOWERCLASS_H



























