#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <waypoint.h>
#include <gamebase.h>
#include "towerclass.h"
#include "unity.h"
class QPainter;
class MainWindow;


class Enemyclass : public QObject
{
    Q_OBJECT
public:
    Enemyclass(Waypoint *startWayPoint, Gamebase *game, QPixmap img,int wave/*const QPixmap &sprite = QPixmap(":/images/yuanshichong1.png")*/);
    ~Enemyclass();


    void draw(QPainter *painter) const;
    void move();

    void getDamage(int damage);
    void getRemoved();

    void getAttacked(Towerclass* attacktower);
    void getLostSight(Towerclass* attacktower);

    QPoint getposition() const;
    virtual void convert_virtual() const=0;

public slots:
    void doActivate();

protected:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    Waypoint *		m_destinationWayPoint;
    Gamebase *	    m_game;

    QList<Towerclass* > m_attackedtowerlist;

    QPixmap         m_enemyimg;
    static const QSize ms_fixedSize;
};

class Monster1 : public Enemyclass
{
public:
    Monster1(Waypoint *startWayPoint, Gamebase *game, int wave=0, const QPixmap &sprite = QPixmap(":/images/yuanshichong1.png"));
    void convert_virtual() const{}

};

class Monster2 : public Enemyclass
{
public:
    void convert_virtual() const{}

    Monster2(Waypoint *startWayPoint, Gamebase *game, int wave=0, const QPixmap &sprite = QPixmap(":/images/Y4.png"));

};



#endif // ENEMYCLASS_H
