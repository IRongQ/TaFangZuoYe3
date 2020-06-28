#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <yinxiao.h>
//用于满足各种按钮的功能

class ButtonClass : public QPushButton
{
    Q_OBJECT
public:
    ButtonClass(QString road);
    void btndown();
    void btnup();

signals:

private:
    //Yinxiao * Playvoice;
};


#endif // BUTTONCLASS_H
