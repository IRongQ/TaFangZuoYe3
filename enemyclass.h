#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <waypoint.h>
#include <gamebase.h>
#include "unity.h"
class QPainter;
class MainWindow;


class Enemyclass : public QObject
{
    Q_OBJECT
public:
    Enemyclass(Waypoint *startWayPoint, Gamebase *game, QPixmap img/*const QPixmap &sprite = QPixmap(":/images/yuanshichong1.png")*/);
    ~Enemyclass();

    void move();
    void getDamage(int damage);
    void getRemoved();
    void draw(QPainter *painter) const;
    QPoint pos() const;
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
    QPixmap         m_enemyimg;


    static const QSize ms_fixedSize;
};

class Monster1 : public Enemyclass
{
public:
    Monster1(Waypoint *startWayPoint, Gamebase *game, const QPixmap &sprite = QPixmap(":/images/yuanshichong1.png"));
    void convert_virtual() const{}

};

class Monster2 : public Enemyclass
{
public:
    void convert_virtual() const{}

    Monster2(Waypoint *startWayPoint, Gamebase *game, const QPixmap &sprite = QPixmap(":/images/Y4.png"));
    void draw(QPainter *painter) const;

private:
    const QPixmap	m_sprite;
};

class Monster3 : public Enemyclass
{

};

#endif // ENEMYCLASS_H
