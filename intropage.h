#ifndef INTROPAGE_H
#define INTROPAGE_H

#include "towerclass.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>

class IntroPage : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *);
    IntroPage(QWidget *parent = nullptr);


signals:
    void back_to_main();

private:

};

#endif // INTROPAGE_H


























