#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include<QString>
class chess : public QWidget
{
    Q_OBJECT
public:
    explicit chess(QWidget *parent = nullptr);

    int _x;//棋子坐标x
    int _y;//棋子坐标y
    int _place;//棋子位置
    int _color;
    int  _dead;
    int _drawed;
    QString _type;//固定每个棋子的_type与_id
    int _id;

    int str;//棋子战斗力
    //int dis[16][16];//棋子与周围四个子距离
   // int _str[16][16];//两棋子战斗力差值

    QString gettext(int i)//获得棋子表面信息后返回
    {

        switch (i) {
        case 0:
            return "将";
        case 16:
            return "帅";
        case 17:
        case 18:
            return "仕";
        case 1:
        case 2:
            return "士";
        case 19:
        case 20:
            return "相";
        case 3:
        case 4:
            return "象";
        case 5:
        case 6:
        case 21:
        case 22:
            return "马";
        case 7:
        case 8:
        case 23:
        case 24:
            return "车";
        case 9:
        case 10:
        case 25:
        case 26:
            return "炮";
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return "卒";
        case 31:
        case 27:
        case 28:
        case 29:
        case 30:
            return  "兵";
        }
         return "错误";
    }



signals:

public slots:
};

#endif // CHESS_H
