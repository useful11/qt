#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "board.h"
#include "board1.h"
#include "board2.h"
#include "rules.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_2_released();

    void on_man_released();

    void on_pushButton_released();

private:
    Ui::Widget *ui;
    board w1;
    board1 w2;
    board2 w3;
    rules w4;


};

#endif // WIDGET_H
