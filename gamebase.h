#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QMainWindow>
#include <QWidget>
#include <QList>

class Enemyclass;
class Monster1;
class Monster2;

class Gamebase
{

public:
    explicit Gamebase(QWidget *parent = nullptr);
    void getHpDamage(int damage = 1);
    void removedEnemy(Enemyclass *enemy);
    virtual bool loadWave(){return true;}
protected:


    int                     m_waves=0;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    QList<Enemyclass *>     Monster_list;
};

#endif // GAMEBASE_H
