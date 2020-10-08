#ifndef BOARD2_H
#define BOARD2_H

#include <QDialog>
#include <QWidget>
#include "chess.h"
#include<QString>
#include<QMouseEvent>
#include<QPushButton>
#include <QEventLoop>
namespace Ui {
class board2;
}

class board2 : public QDialog
{
    Q_OBJECT

public:
    explicit board2(QWidget *parent = 0);
    void getplace();//初始化时获得棋子的随机位置
    void place_point(int a,int&x,int &y);//初始化时获得棋子的随机位置坐标
    QString getText();//获得棋面信息
    void deadchess(int a,int &x,int &y);//将死棋置于下面棋盘
    bool rule();




       void result( int m[][3],int a,int b,int c,int d);
       void result2( int m[][3],int a,int b,int c,int d);
        void choice(int a[][3],int n,int h);
        void black(int b[][3],int o,int w,int k);
        void black1(int b[][3],int o,int w,int k);
          void result1(int b[][3],int a,int e);
          void result3(int b[][3],int a,int e);


            ~board2();

  protected :void paintEvent(QPaintEvent*);//绘制棋盘和棋子



private:
  Ui::board2 *ui;
    int l;//棋盘格子长度
    int r;
    chess _a[32];//32颗棋子
    int flag1;//颜色标记
    int flag2;//鼠标之前点击位置
    int flag3;//鼠标最新点击位置
    int q;
    int A[32][3];
    int A1[32][3];
    int v;
    int v1;
    int step;


private:

};

#endif // BOARD2_H
