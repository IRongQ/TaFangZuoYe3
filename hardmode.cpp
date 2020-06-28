#include "hardmode.h"
#include "mainwindow.h"
#include "buttonclass.h"
#include "towerclass.h"
#include "enemyclass.h"
#include "yinxiao.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>


Hardmode::Hardmode(QWidget *parent)
{
    QMediaPlaylist *playlist=new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/sound/hardbgm.wav"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();

    this->setFixedSize(1280,720);
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
    uplevelbtn->move(1100,100);
    uplevelbtn->setParent(this);
    connect(uplevelbtn,&ButtonClass::clicked,this,[=](){
        uplevelbtn->btndown();
        uplevelbtn->btnup();
        flag=1;
    });

    ButtonClass *removebtn = new ButtonClass(":/images/remove.png");
    removebtn->move(1100,160);
    removebtn->setParent(this);
    connect(removebtn,&ButtonClass::clicked,this,[=](){
        removebtn->btndown();
        removebtn->btnup();
        flag=2;
    });

    addhardwaypoint1();
    addhardwaypoint2();
    addhardwaypoint3();
    loadTowerposition();


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}
void Hardmode::paintEvent(QPaintEvent *){  //每次进入主界面都会调用paintEvent函数
    if (m_gameLost || m_gameWin)
    {
        player->stop();
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
    QPixmap pixmap(":/images/hardmode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    drawInfo(&painter);
    /*foreach (const Waypoint *wayPoint, hard_waypointlist)
        wayPoint->draw(&painter);
    foreach (const Waypoint *wayPoint, hard_waypointlist2)
        wayPoint->draw(&painter);
    foreach (const Waypoint *wayPoint, hard_waypointlist3)
        wayPoint->draw(&painter); */
    foreach (const TowerPosition &towerpositionlist, m_positionlist)
        towerpositionlist.draw(&painter);
    foreach (const Towerclass *tower, m_Towerlist)
        tower->draw(&painter);
    foreach (const Enemyclass *enemy, Monster_list)
        enemy->draw(&painter);
    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

}
void Hardmode::addhardwaypoint1(){
    Waypoint *wayPoint1 = new Waypoint(QPoint(1120,525));
    hard_waypointlist.push_back(wayPoint1);

    Waypoint *wayPoint2 = new Waypoint(QPoint(285,525));
    hard_waypointlist.push_back(wayPoint2);
    wayPoint2->setnext(wayPoint1);

    Waypoint *wayPoint3 = new Waypoint(QPoint(315,325));
    hard_waypointlist.push_back(wayPoint3);
    wayPoint3->setnext(wayPoint2);

    Waypoint *wayPoint4 = new Waypoint(QPoint(965,325));
    hard_waypointlist.push_back(wayPoint4);
    wayPoint4->setnext(wayPoint3);

    Waypoint *wayPoint5 = new Waypoint(QPoint(940,150));
    hard_waypointlist.push_back(wayPoint5);
    wayPoint5->setnext(wayPoint4);

    Waypoint *wayPoint6 = new Waypoint(QPoint(245, 150));
    hard_waypointlist.push_back(wayPoint6);
    wayPoint6->setnext(wayPoint5);
}
void Hardmode::addhardwaypoint2(){
    Waypoint *wayPoint4 = new Waypoint(QPoint(1120,525));
    hard_waypointlist2.push_back(wayPoint4);

    Waypoint *wayPoint5 = new Waypoint(QPoint(285,525));
    hard_waypointlist2.push_back(wayPoint5);
    wayPoint5->setnext(wayPoint4);

    Waypoint *wayPoint6 = new Waypoint(QPoint(315,325));
    hard_waypointlist2.push_back(wayPoint6);
    wayPoint6->setnext(wayPoint5);

    Waypoint *wayPoint7 = new Waypoint(QPoint(1110,325));
    hard_waypointlist2.push_back(wayPoint7);
    wayPoint7->setnext(wayPoint6);
}
void Hardmode::addhardwaypoint3(){
    Waypoint *wayPoint1 = new Waypoint(QPoint(1120,525));
    hard_waypointlist3.push_back(wayPoint1);

    Waypoint *wayPoint6 = new Waypoint(QPoint(245, 130));
    hard_waypointlist3.push_back(wayPoint6);
    wayPoint6->setnext(wayPoint1);
}

bool Hardmode::loadWave()
{
    if (m_waves >= 6)
        return false;
    Waypoint *startWayPoint1 = hard_waypointlist.back();
    int enemyStartInterval1[] = { 100, 500, 1200, 1900, 3000, 6000 };
    for (int i = 0; i < 6; ++i)
    {
        Monster1 *enemy = new Monster1(startWayPoint1, this,m_waves);
        Monster_list.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }
    Waypoint *startWayPoint2 = hard_waypointlist2.back();
    int enemyStartInterval2[] = { 200, 600, 900, 1500, 3100, 6100 };
    for (int i = 0; i < 6; ++i)
    {
        Monster1 *enemy = new Monster1(startWayPoint2, this,m_waves);
        Monster_list.push_back(enemy);
        QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
    }
    Waypoint *startWayPoint3 = hard_waypointlist3.back();
    int enemyStartInterval3[] = { 8000, 10000, 13000, 20000, 26000, 30000 };
    for (int i = 0; i < 6; ++i)
    {
        Monster2 *enemy = new Monster2(startWayPoint3, this,m_waves);
        Monster_list.push_back(enemy);
        QTimer::singleShot(enemyStartInterval3[i], enemy, SLOT(doActivate()));
    }
    return true;
}



void Hardmode::updateMap()
{

    foreach (Enemyclass *enemy, Monster_list)
        enemy->move();
    foreach (Towerclass *tower, m_Towerlist)
        tower->checkEnemyInRange();
    update();
}

void Hardmode::gameStart(){
    loadWave();
}

void Hardmode::loadTowerposition(){
    QPoint pos[] =
    {
        QPoint(285, 185),
        QPoint(397, 185),
        QPoint(503, 185),
        QPoint(615, 185),
        QPoint(720, 185),
        QPoint(495, 380),
        QPoint(610, 380),
        QPoint(730, 380),
        QPoint(845, 380),
        QPoint(960, 380)

    };
        int positionlistsize = sizeof(pos) / sizeof(pos[0]);
        for (int i = 0; i < positionlistsize ; ++i)
            m_positionlist.push_back(pos[i]);

}
