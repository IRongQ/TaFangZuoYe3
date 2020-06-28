#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemyclass;
class Gamebase;

class Bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemyclass *target,
           Gamebase *game, const QPixmap &sprite = QPixmap(":/images/bullet.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemyclass *    m_target;
    Gamebase *	    m_game;
    int				m_damage;

    static const QSize ms_fixedSize;
};

#endif // BULLET_H
