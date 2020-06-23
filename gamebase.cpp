#include "gamebase.h"

Gamebase::Gamebase(QWidget *parent)
    :m_waves(0)
    ,m_playerHp(2)
    ,m_playrGold(1000)
{

}

void Gamebase::getHpDamage(int damage){

}



void Gamebase::removedEnemy(Enemyclass *enemy){
    Q_ASSERT(enemy);
    Monster_list.removeOne(enemy);
    delete enemy;
    if(Monster_list.empty()){
        ++m_waves;

    }
}


