#ifndef BOARD_H
#define BOARD_H

#include<QDialog>
#include<QWidget>
#include "chess.h"
#include "rules.h"
#include<QString>
#include<QMouseEvent>
#include<QPushButton>
#include<QEventLoop>
#include<QTextEdit>
namespace Ui {
class board;
}

class board : public QDialog
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);//绘制棋盘和棋子
    void mouseReleaseEvent(QMouseEvent*);//鼠标点击界面后获得点击点的坐标
    void rulesshow();

    void getplace();//初始化时获得棋子的随机位置
    void place_point(int a,int&x,int &y);//初始化时获得棋子的随机位置坐标
    QString getText();//获得棋面信息


    bool mousepres1(int &a);//判断点击点是否在棋子上
    int  mousepres2(int x,int y);//判断鼠标点击是否在合法位置,返回位置
    bool rightprocess(bool a,int b,int x,int y);//判断过程是否正确
    int ifpao(bool a,int x,int y);//判断炮是否可以符合规则
    int pao_useed(int x,int y);
    bool getit(int a,int x,int y);//判断是否吃子
    void deadchess(int a,int &x,int &y);//将死棋置于下面棋盘

    QTextEdit w1;
     bool rule();



       void result( int m[][3],int a,int b,int c,int d);
        void choice(int a[][3],int n,int h);
        void black(int b[][3],int o,int w,int k);
          void result1(int b[][3],int a,int e);
            void morechoice(int a[][3],int n);
 ~board();
private slots:
             void on_pushButton_released();

             void on_pushButton_clicked();

private:
    Ui::board *ui;
    int l;//棋盘格子长度
    int r;
    chess _a[32];//32颗棋子
    int flag1;//颜色标记
    int flag2;//鼠标之前点击位置
    int flag3;//鼠标最新点击位置
    int q;
    int A[32][3];
    int v;
    int step;
    rules w3;




};

#endif // BOARD_H
