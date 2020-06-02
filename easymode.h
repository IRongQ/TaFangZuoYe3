#ifndef EASYMODE_H
#define EASYMODE_H

#include "towerclass.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>

class Easymode : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *);
    explicit Easymode(QWidget *parent = nullptr);

signals:
    void back_to_main();
public slots:
};

#endif // EASYMODE_H
