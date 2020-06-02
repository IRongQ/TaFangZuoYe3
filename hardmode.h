#ifndef HARDMODE_H
#define HARDMODE_H

#include "towerclass.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>

class Hardmode : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *);
    explicit Hardmode(QWidget *parent = nullptr);

signals:
    void back_to_main();
public slots:
};

#endif // HARDMODE_H
