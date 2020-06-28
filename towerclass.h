#ifndef TOWERCLASS_H
#define TOWERCLASS_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QMediaPlayer>
#include "towerposition.h"
#include "gamebase.h"
#include "yinxiao.h"

class QPainter;
class Enemyclass;
class MainWindow;
class QTimer;
class Gamebase;


class Towerclass:public QObject
{
    Q_OBJECT
public:
    Towerclass(QPoint pos, Gamebase *game, const QPixmap &sprite = QPixmap(":/images/firegun.png"));
    ~Towerclass();
    void draw(QPainter * painter) const;

    void targetKilled();
    //void removeBullet();
    void checkEnemyInRange();
    void chooseEnemyForAttack(Enemyclass *enemy);
    void attackEnemy();
    void lostSightOfEnemy();
    const QPoint centerPos() const;

    void Uplevel();

    bool containPoint(const QPoint &pos) const;
    bool        hasenemy;

private slots:
    void shootWeapon();

signals:
    void removeTower();

private:
    Gamebase*   m_game;

    bool	    m_attacking;
    int         m_attackrange;
    int         m_damage;
    int         m_firerate;                //再次攻击敌人的时间间隔



    Enemyclass*       m_chooseEnemy;
    QTimer *          m_fireRateTimer;

    const QPixmap     m_sprite;
    const QPoint      m_pos;

    //Yinxiao * Playvoice;

    static const QSize ms_fixedSize;
};

#endif // TOWERCLASS_H



























