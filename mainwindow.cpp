#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QTimer>
#include "intropage.h"
#include "buttonclass.h"
#include "easymode.h"
#include "hardmode.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{//设置大小

    this->setFixedSize(1450,750);
    ui->setupUi(this);



  //生成简单模式
    ButtonClass *Starteasy = new ButtonClass(":/images/easychoice.jpg");
    Starteasy->move(370,490);
    Starteasy->setParent(this);

    connect(Starteasy,&ButtonClass::clicked,this,[=](){
        Starteasy->btndown();
        Starteasy->btnup();
        Easymode * easymode = new Easymode;
        QTimer::singleShot(300,this,[=](){       //计时装置，让动画效果得以显现
            this->hide();
            easymode->show();

        });
        connect(easymode,&Easymode::back_to_main,this,[=](){
            easymode->close();
            this->show();
    });

    });
  //生成困难模式
    ButtonClass *Starthard = new ButtonClass(":/images/hardchoice.jpg");
    Starthard->move(638,490);
    Starthard->setParent(this);

    connect(Starthard,&ButtonClass::clicked,this,[=](){
        Starthard->btndown();
        Starthard->btnup();
        Hardmode * hardmode = new Hardmode;
        QTimer::singleShot(300,this,[=](){       //计时装置，让动画效果得以显现
            this->hide();
            hardmode->show();
        });
        connect(hardmode,&Hardmode::back_to_main,this,[=](){
            hardmode->close();
            this->show();
    });

    });

  //生成介绍页面
      ButtonClass *btn = new ButtonClass(":/images/introchoice.jpg");
      btn->move(40,30);
      btn->setParent(this);
      IntroPage * introductionpage = new IntroPage;
      connect(btn,&ButtonClass::clicked,this,[=](){
      //按钮动画
        btn->btndown();
        btn->btnup();
        QTimer::singleShot(300,this,[=](){       //计时装置，让动画效果得以显现
            this->hide();
            introductionpage->show();
        });
     });
      //退出介绍页面
     connect(introductionpage,&IntroPage::back_to_main,this,[=](){
        introductionpage->hide();
        this->show();
     });
  //生成退出
     ButtonClass *quit = new ButtonClass(":/images/quitchoice.png");
     quit->move(904,490);
     quit->setParent(this);
     connect(quit,&ButtonClass::clicked,this,&QMainWindow::close);
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *){    //每次进入主界面都会调用paintEvent函数
    QPainter painter(this);
    QPixmap pixmap(":/images/mainpage.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}





















