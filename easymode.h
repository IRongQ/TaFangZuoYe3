#ifndef EASYMODE_H
#define EASYMODE_H
#include "mainwindow.h"
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


class Easymode : public Gamebase
{
    Q_OBJECT
    friend class Gamebase;
public:
    void paintEvent(QPaintEvent *);
    explicit Easymode(QWidget *parent = nullptr);
    void addeasywaypoint();
    bool loadWave();
    void loadTowerposition();


private slots:
    void updateMap();
    void gameStart();

private:

    QList<Waypoint *> easy_waypointlist;


signals:
    void back_to_main();
public slots:
};

#endif // EASYMODE_H
