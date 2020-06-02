#include "hardmode.h"
#include "buttonclass.h"
#include "towerclass.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>


Hardmode::Hardmode(QWidget *parent) : QMainWindow(parent)
{
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
        });
    });
}
void Hardmode::paintEvent(QPaintEvent *){  //每次进入主界面都会调用paintEvent函数
    QPainter painter(this);
    QPixmap pixmap(":/images/hardmode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
