#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QMainWindow>
#include <QWidget>
#include <QList>
#include <QMediaPlayer>
#include "towerposition.h"
#include "towerclass.h"
#include "bullet.h"
#include "yinxiao.h"


class Enemyclass;
class Monster1;
class Monster2;
class Towerclass;

class Gamebase:public QMainWindow
{

public:
    explicit Gamebase(QWidget *parent = nullptr);
    void getHpDamage(int damage = 1);
    void removedEnemy(Enemyclass *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void removeTower(Towerclass *tower);

    void doGameOver();
    void drawInfo(QPainter *painter);
    void dieMoney(int gold);

    bool canbuytower();

    virtual bool loadWave(){return true;}
    virtual void loadTowerposition(){}

    QList<Enemyclass* > monsterlist() const;
protected:

    void mousePressEvent(QMouseEvent *event);

    int                     m_waves=0;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameLost;
    bool					m_gameWin;
    QList<Enemyclass *>     Monster_list;
    QList<TowerPosition>    m_positionlist;
    QList<Towerclass* >     m_Towerlist;
    QList<Bullet* >         m_bulletList;

    QMediaPlayer     *player= new QMediaPlayer;
    int flag = 0;

    //Yinxiao  * Playvoice;
};

#endif // GAMEBASE_H
