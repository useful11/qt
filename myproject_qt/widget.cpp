#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include "board.h"
#include "board1.h"
#include "board2.h"
#include "rules.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle( QString("象棋暗棋比大小"));
    this->setFixedSize(750,600);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_released()
{
   w1.show();//人机
   this->close();
}

void Widget::on_man_released()
{

    w2.show();//人人
    this->close();
}

void Widget::on_pushButton_released()
{
    w3.show();//机器
    this->close();
}
