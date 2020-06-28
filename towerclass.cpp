#include "towerclass.h"
#include "enemyclass.h"
#include "gamebase.h"
#include "yinxiao.h"
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QTimer>
#include <QAction>
#include <QObject>


const QSize Towerclass::ms_fixedSize(44, 44);

Towerclass::Towerclass(QPoint pos,Gamebase *game,const QPixmap &sprite):
    m_attacking(false)
    ,m_game(game)
    ,m_pos(pos)
    ,m_sprite(sprite)
    ,m_attackrange(150)
    ,m_damage(15)
    ,m_chooseEnemy(NULL)
    ,m_firerate(1000)
    ,hasenemy(false)

{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));


}
void Towerclass::draw(QPainter *painter) const{
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackrange, m_attackrange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2-13, -ms_fixedSize.height() / 2-15);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

Towerclass::~Towerclass(){
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

bool Towerclass::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + ms_fixedSize.height());
    return isXInHere && isYInHere;
}

void Towerclass::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {

        if (!collisionWithCircle(m_pos, m_attackrange, m_chooseEnemy->getposition(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemyclass *> enemyList = m_game->monsterlist();
        foreach (Enemyclass *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackrange, enemy->getposition(), 1))
            {
                chooseEnemyForAttack(enemy);
                hasenemy=true;
                break;
            }
        }
    }
}

void Towerclass::chooseEnemyForAttack(Enemyclass *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Towerclass::attackEnemy()
{
    m_fireRateTimer->start(m_firerate);
}


void Towerclass::targetKilled(){
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
}

void Towerclass::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->getposition(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    shootvoice();
    //Playvoice->playvoice(shoot);
    m_game->addBullet(bullet);
}

void Towerclass::lostSightOfEnemy()
{
    if (m_chooseEnemy!=NULL){
        m_chooseEnemy->getLostSight(this);
        m_chooseEnemy = NULL;
        m_fireRateTimer->stop();
    }
}

void Towerclass::Uplevel(){
    m_damage += 5;
    m_attackrange += 20;
    uplevelvoice();
   // Playvoice->playvoice(uplevel);
}

const QPoint Towerclass::centerPos() const
{
    return m_pos ;
}

