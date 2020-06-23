#include "enemyclass.h"
#include "waypoint.h"
#include "mainwindow.h"
#include "gamebase.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
static const int Health_Bar_Width = 30;
const QSize Enemyclass::ms_fixedSize(40, 40);

Enemyclass::Enemyclass(Waypoint *startWayPoint, Gamebase *game, QPixmap img)
    : QObject(0)
    , m_active(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , m_walkingSpeed(1.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWaypoint())
    , m_game(game)
    ,m_enemyimg(img)
{
}

void Enemyclass::move()
{
    if (!m_active)
        return;
    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWaypoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWaypoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    // 向量标准化
    double movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右

}


Enemyclass::~Enemyclass()
{
    //m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemyclass::doActivate(){
    m_active=true;
}

Monster1::Monster1(Waypoint *startWayPoint, Gamebase *game, const QPixmap &sprite)
    :Enemyclass(startWayPoint,game,sprite)
{
}

Monster2::Monster2(Waypoint *startWayPoint, Gamebase *game, const QPixmap &sprite )
    :Enemyclass(startWayPoint,game,sprite)
{
}
void Enemyclass::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 + 5 , -ms_fixedSize.height() / 2 );
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);

    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_enemyimg);
    painter->restore();
}


