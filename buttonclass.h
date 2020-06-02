#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H

#include <QWidget>
#include <QPushButton>
//用于满足各种按钮的功能

class ButtonClass : public QPushButton
{
    Q_OBJECT
public:
    ButtonClass(QString road);
    void btndown();
    void btnup();

signals:

public slots:
};

#endif // BUTTONCLASS_H
