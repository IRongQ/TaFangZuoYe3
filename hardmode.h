#ifndef HARDMODE_H
#define HARDMODE_H

#include "towerclass.h"
#include "waypoint.h"
#include "gamebase.h"
#include "enemyclass.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>

class Hardmode : public QMainWindow,public Gamebase
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *);
    explicit Hardmode(QWidget *parent = nullptr);
    void addhardwaypoint1();
    void addhardwaypoint2();
    void addhardwaypoint3();
bool loadWave();
private:


private slots:
    void updateMap();
    void gameStart();
private:

    QList<Waypoint *> hard_waypointlist;
    QList<Waypoint *> hard_waypointlist2;
    QList<Waypoint *> hard_waypointlist3;

signals:
    void back_to_main();
public slots:
};

#endif // HARDMODE_H
