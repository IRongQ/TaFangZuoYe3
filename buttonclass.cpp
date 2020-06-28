#include "buttonclass.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QMediaPlayer>

ButtonClass::ButtonClass(QString road):QPushButton(0)
{
    QPixmap pixmap(road);
    this->setFixedSize(pixmap.width(),pixmap.height());  //按钮大小和图片大小保持一致
    this->setStyleSheet("QPushButton{border:Opx;}");  //使其改变样式
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}

void ButtonClass::btndown(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->start();
}

void ButtonClass::btnup(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->start();
    buttonvoice();
    //Playvoice->playvoice(buttonclick);
}






















