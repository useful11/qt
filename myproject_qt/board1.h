#ifndef BOARD1_H
#define BOARD1_H

#include <QDialog>
#include<QWidget>
#include "chess.h"
#include "rules.h"
#include<QString>
#include<QMouseEvent>
#include<QPushButton>
#include<QEventLoop>
namespace Ui {
class board1;
}

class board1 : public QDialog
{
    Q_OBJECT

public:
    explicit board1(QWidget *parent = 0);
    chess _a[32];//32颗棋子
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
    bool rule();

    ~board1();

  protected :void paintEvent(QPaintEvent*);//绘制棋盘和棋子
             void mouseReleaseEvent(QMouseEvent*);//鼠标点击界面后获得点击点的坐标



private slots:
             void on_pushButton_released();

             void on_pushButton_clicked();

private:
    Ui::board1 *ui;
    int l;//棋盘格子长度
    int r;

    int flag1;//颜色标记
    int flag2;//鼠标之前点击位置
    int flag3;//鼠标最新点击位置
    rules w4;
    QPushButton p1;

    int q;//红黑交换



};

#endif // BOARD1_H
