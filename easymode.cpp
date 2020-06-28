#include "easymode.h"
#include "mainwindow.h"
#include "buttonclass.h"
#include "towerclass.h"
#include "waypoint.h"
#include "gamebase.h"
#include "towerposition.h"
#include "enemyclass.h"
#include "yinxiao.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include <QtDebug>
#include <QMediaPlaylist>
#include <QMediaPlayer>


Easymode::Easymode(QWidget *parent)
{
    this->setFixedSize(1280,720);

    addeasywaypoint();
    loadTowerposition();



    QMediaPlaylist *playlist=new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/sound/bgm.wav"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();

    ButtonClass *backbtn = new ButtonClass(":/images/backchoice.png");
    backbtn->move(1100,40);
    backbtn->setParent(this);
   //转回主界面设置
    connect(backbtn,&ButtonClass::clicked,this,[=](){
        backbtn->btndown();
        backbtn->btnup();
        QTimer::singleShot(300,this,[=](){
            emit back_to_main();
            player->stop();
        });
    });

    ButtonClass *uplevelbtn = new ButtonClass(":/images/uplevel.png");
    uplevelbtn->move(1100,140);
    uplevelbtn->setParent(this);
    connect(uplevelbtn,&ButtonClass::clicked,this,[=](){
        uplevelbtn->btndown();
        uplevelbtn->btnup();
        flag=1;
    });

    ButtonClass *removebtn = new ButtonClass(":/images/remove.png");
    removebtn->move(1100,240);
    removebtn->setParent(this);
    connect(removebtn,&ButtonClass::clicked,this,[=](){
        removebtn->btndown();
        removebtn->btnup();
        flag=2;
    });

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);      // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}
void Easymode::paintEvent(QPaintEvent *){  //每次进入主界面都会调用paintEvent函数
    if (m_gameLost || m_gameWin)
    {

        player->stop();
        //Playvoice->playvoice(gamewin);
        if(m_gameLost){
        QString text = "YOU LOST!!!";
        //Playvoice->playvoice(gamewin);
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
        }
        QPainter painter1(this);
        QPixmap easywin(":/images/easywin.jpg");
        painter1.drawPixmap(0,0,this->width(),this->height(),easywin);
        return;
    }
    QPainter painter(this);
    QPixmap pixmap(":/images/easymode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    /*foreach (const Waypoint *wayPoint, easy_waypointlist)
        wayPoint->draw(&painter);*/
    drawInfo(&painter);
    foreach (const TowerPosition &towerposition, m_positionlist)
        towerposition.draw(&painter);
    foreach (const Towerclass *tower, m_Towerlist)
        tower->draw(&painter);
    foreach (const Enemyclass *enemy, Monster_list)
        enemy->draw(&painter);
    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);
}

void Easymode::addeasywaypoint()
{
    Waypoint *wayPoint1 = new Waypoint(QPoint(200,285));
    easy_waypointlist.push_back(wayPoint1);

    Waypoint *wayPoint2 = new Waypoint(QPoint(320,285));
    easy_waypointlist.push_back(wayPoint2);
    wayPoint2->setnext(wayPoint1);

    Waypoint *wayPoint3 = new Waypoint(QPoint(305,372));
    easy_waypointlist.push_back(wayPoint3);
    wayPoint3->setnext(wayPoint2);

    Waypoint *wayPoint4 = new Waypoint(QPoint(530,372));
    easy_waypointlist.push_back(wayPoint4);
    wayPoint4->setnext(wayPoint3);

    Waypoint *wayPoint5 = new Waypoint(QPoint(535,285));
    easy_waypointlist.push_back(wayPoint5);
    wayPoint5->setnext(wayPoint4);

    Waypoint *wayPoint6 = new Waypoint(QPoint(745,285));
    easy_waypointlist.push_back(wayPoint6);
    wayPoint6->setnext(wayPoint5);

    Waypoint *wayPoint7 = new Waypoint(QPoint(1060, 360));
    easy_waypointlist.push_back(wayPoint7);
    wayPoint7->setnext(wayPoint6);
}

bool Easymode::loadWave()
{
    if (m_waves >= 6)
        return false;
    Waypoint *startWayPoint = easy_waypointlist.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };

    for (int i = 0; i < 6; ++i)
    {
        Monster1 *enemy = new Monster1(startWayPoint, this,m_waves);
        Monster_list.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}

void Easymode::updateMap()
{
    foreach (Enemyclass *enemy, Monster_list)
        enemy->move();
    foreach (Towerclass *tower, m_Towerlist)
        tower->checkEnemyInRange();
    update();
}

void Easymode::gameStart(){
    loadWave();
}

void Easymode::loadTowerposition(){
    QPoint pos[] =
        {
            QPoint(310, 155),
            QPoint(397, 240),
            QPoint(380, 430),
            QPoint(615, 155),
            QPoint(610, 335),
            QPoint(850, 440)

        };
        int positionlistsize = sizeof(pos) / sizeof(pos[0]);
        for (int i = 0; i < positionlistsize ; ++i)
            m_positionlist.push_back(pos[i]);

}




