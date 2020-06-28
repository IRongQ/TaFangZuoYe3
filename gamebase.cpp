#include "gamebase.h"
#include <QPainter>
#include "yinxiao.h"

static const int TowerPrice = 300;
static const int levelup = 500;



Gamebase::Gamebase(QWidget *parent)
    :m_waves(0)
    ,m_playerHp(5)
    ,m_playrGold(1000)
    ,m_gameLost(false)
    ,m_gameWin(false)
{


}

bool Gamebase::canbuytower(){
    if (m_playrGold >= TowerPrice)
            return true;
        return false;
}

void Gamebase::getHpDamage(int damage){
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void Gamebase::doGameOver()
{
    if (!m_gameLost)
    {
        m_gameLost = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void Gamebase::drawInfo(QPainter *painter){
        QFont font1("Courier",15,QFont::Bold,true);
        font1.setLetterSpacing(QFont::AbsoluteSpacing,7);
        painter->setFont(font1);
        painter->setPen(QPen(Qt::red));
        painter->drawText(300, 50, QString("HP : %1").arg(m_playerHp));
        painter->drawText(500, 50, QString("GOLD : %1").arg(m_playrGold));
        painter->drawText(800, 50,QString("WAVE : %1").arg(m_waves + 1));
}

void Gamebase::mousePressEvent(QMouseEvent *event){
    QPoint pressPos = event->pos();
    auto it = m_positionlist.begin();
    while (it != m_positionlist.end())
    {
        if (canbuytower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_playrGold -= TowerPrice;
            it->setHasTower();
            Towerclass *tower = new Towerclass(it->centerPos(), this);
            settowervoice();
            //Playvoice->playvoice(settower);
            m_Towerlist.push_back(tower);
            update();
            break;
        }
        foreach (Towerclass *tower,m_Towerlist){
            if(m_playrGold>=600&&it->containPoint(pressPos)&&it->hasTower()&&tower->containPoint(pressPos)&&flag==1){
                tower->Uplevel();
                m_playrGold -= 600;
                flag=0;
            }
            if(it->containPoint(pressPos)&&it->hasTower()&&tower->containPoint(pressPos)&&flag==2&&it->centerPos()==tower->centerPos()){
                if(tower->hasenemy)
                {
                    tower->hasenemy=false;
                    tower->lostSightOfEnemy();
                }
                m_playrGold += 150;
                it->setHasTower(false);
                removeTower(tower);

                flag=0;
            }
        }
        ++it;
    }
}



QList<Enemyclass *> Gamebase::monsterlist() const
{
    return Monster_list;
}

void Gamebase::addBullet(Bullet *bullet){
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void Gamebase::removedEnemy(Enemyclass *enemy){
    Q_ASSERT(enemy);
    Monster_list.removeOne(enemy);
    monsterdievoice();
    //Playvoice->playvoice(monsterdie);
    delete enemy;
    if(Monster_list.empty()){
        ++m_waves;
        if(!loadWave())
        {
            gamewinvoice();
            m_gameWin = true;
        }
    }
}

void Gamebase::removeTower(Towerclass *tower){
    Q_ASSERT(tower);
    m_Towerlist.removeOne(tower);
    removetowervoice();
    //Playvoice->playvoice(removetower);
    delete tower;
}

void Gamebase::removedBullet(Bullet *bullet){
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void Gamebase::dieMoney(int gold){
    m_playrGold += gold;
        update();
}
