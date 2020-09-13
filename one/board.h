#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "chess.h"
#include<QString>
class board : public QWidget
{
    Q_OBJECT

public:
    board(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);//绘制棋盘
    chess _a[32];
    void getplace();//获得随机位置
    void place_point();//获得随机位置坐标
    QString getText();//获得棋面信息
    QPoint center(int x,int y);//移动过后棋子的中心点位置获取


    ~board();
};

#endif // BOARD_H
