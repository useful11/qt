#include "board.h"
#include<QPainter>
#include<QString>
#include<QtGlobal>
#include<QTime>
#include<QDebug>
#include<QRect>
board::board(QWidget *parent)
    : QWidget(parent)
{
    //初始化每一个棋子
     for(int i=0;i<16;i++)
     {
         _a[i]._x=0;
         _a[i]._y=0;
         _a[i]._place=0;
         _a[i]._color=1;    //0表示红色，1表示黑色
         _a[i]._dead=0;     //0表示仍然存活，1表示被吃掉
         _a[i]._drawed=0;   //0表示仍未被翻面，1表示已翻面

     }
     _a[0]._type="将";_a[0]._id=0;
     _a[1]._type="士";_a[1]._id=1;
     _a[2]._type="士";_a[2]._id=2;
     _a[3]._type="象";_a[3]._id=3;
     _a[4]._type="象";_a[4]._id=4;
     _a[5]._type="马";_a[5]._id=5;
     _a[6]._type="马";_a[6]._id=6;
     _a[7]._type="车";_a[7]._id=7;
     _a[8]._type="车";_a[8]._id=8;
     _a[9]._type="炮";_a[9]._id=9;
     _a[10]._type="炮";_a[10]._id=10;
     _a[11]._type="卒";_a[11]._id=11;
     _a[12]._type="卒";_a[12]._id=12;
     _a[13]._type="卒";_a[13]._id=13;
     _a[14]._type="卒";_a[14]._id=14;
     _a[15]._type="卒";_a[15]._id=15;
     for(int i=16;i<32;i++)
     {
         _a[i]._x=0;
         _a[i]._y=0;
         _a[i]._place=0;
         _a[i]._color=0;    //0表示红色，1表示黑色
         _a[i]._dead=0;     //0表示仍然存活，1表示被吃掉
         _a[i]._drawed=0 ;   //0表示仍未被翻面，1表示已翻面
     }
     _a[16]._type="帅";_a[16]._id=16;
     _a[17]._type="仕";_a[17]._id=17;
     _a[18]._type="仕";_a[18]._id=18;
     _a[19]._type="相";_a[19]._id=19;
     _a[20]._type="相";_a[20]._id=20;
     _a[21]._type="马";_a[21]._id=21;
     _a[22]._type="马";_a[22]._id=22;
     _a[23]._type="车";_a[23]._id=23;
     _a[24]._type="车";_a[24]._id=24;
     _a[25]._type="炮";_a[25]._id=25;
     _a[26]._type="炮";_a[26]._id=26;
     _a[27]._type="兵";_a[27]._id=27;
     _a[28]._type="兵";_a[28]._id=28;
     _a[29]._type="兵";_a[29]._id=29;
     _a[30]._type="兵";_a[30]._id=30;
     _a[31]._type="兵";_a[31]._id=31;
     //初始化完成
     qDebug()<<_a[0]._type;
     //获得随机位置
     getplace();
     place_point();
}


void board::paintEvent(QPaintEvent *)
{   QPainter painter(this);
    //画棋盘
    int L=60;//棋盘间距
    //画10条横线
    for(int i=1;i<=10;i++)
       painter.drawLine(QPoint(L,i*L),QPoint(9*L,i*L));
    //画9条竖线
    for(int i=1;i<=9;i++)
       if(i==1||i==9)
          painter.drawLine(QPoint(i*L,L),QPoint(i*L,10*L));
       else
       { painter.drawLine(QPoint(i*L,L),QPoint(i*L,5*L));
         painter.drawLine(QPoint(i*L,6*L),QPoint(i*L,10*L));

       }

    for(int t=0;t<32;t++)
      {QRect rect =QRect(_a[t]._x-25,_a[t]._y-25,50,50);
        painter.drawEllipse(QPoint(_a[t]._x,_a[t]._y),25,25);//棋子半径为25
        //if(_a[t]._drawed==1)
            painter.drawText(rect ,_a[t].gettext(_a[t]._id),QTextOption(Qt::AlignCenter));//判断棋子是否翻转，是否需要显示棋面
       }
}

void board::getplace()
{ int i,j;
  QList<int> numbersList;
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  for(i=0;i<32;i++)
  {
      numbersList.append(qrand()%32);
      bool flag=true;
      while(flag)
      {
          for(j=0;j<i;j++)
             if(numbersList[i]==numbersList[j])
                break;
          if(j<i)
             numbersList[i]=rand()%32;
          if(j==i)
              flag=!flag;
      }
  }
    for(i=0;i<32;i++)
    {
       _a[i]._place=numbersList[i];
    }
}

void board::place_point()
{
    for(int i=0;i<32;i++){
        switch (_a[i]._place+=0) {
        case 31:{_a[i]._x=8*60+30;_a[i]._y=4*60+30;}
                break;
        case 30:{_a[i]._x=7*60+30;_a[i]._y=4*60+30;}
                break;
        case 29:{_a[i]._x=6*60+30;_a[i]._y=4*60+30;}
                break;
        case 28:{_a[i]._x=5*60+30;_a[i]._y=4*60+30;}
                break;
        case 27:{_a[i]._x=4*60+30;_a[i]._y=4*60+30;}
                break;
        case 26:{_a[i]._x=3*60+30;_a[i]._y=4*60+30;}
                break;
        case 25:{_a[i]._x=2*60+30;_a[i]._y=4*60+30;}
                break;
        case 24:{_a[i]._x=60+30;_a[i]._y=4*60+30;}//第四列
                break;
        case 23:{_a[i]._x=8*60+30;_a[i]._y=3*60+30;}
                break;
        case 22:{_a[i]._x=7*60+30;_a[i]._y=3*60+30;}
                break;
        case 21:{_a[i]._x=6*60+30;_a[i]._y=3*60+30;}
                break;
        case 20:{_a[i]._x=5*60+30;_a[i]._y=3*60+30;}
                break;
        case 19:{_a[i]._x=4*60+30;_a[i]._y=3*60+30;}
                break;
        case 18:{_a[i]._x=3*60+30;_a[i]._y=3*60+30;}
                break;
        case 17:{_a[i]._x=2*60+30;_a[i]._y=3*60+30;}
                break;
        case 16:{_a[i]._x=60+30;_a[i]._y=3*60+30;}//第三列
                break;
        case 15:{_a[i]._x=8*60+30;_a[i]._y=2*60+30;}
                break;
        case 14:{_a[i]._x=7*60+30;_a[i]._y=2*60+30;}
                break;
        case 13:{_a[i]._x=6*60+30;_a[i]._y=2*60+30;}
                break;
        case 12:{_a[i]._x=5*60+30;_a[i]._y=2*60+30;}
                break;
        case 11:{_a[i]._x=4*60+30;_a[i]._y=2*60+30;}
                break;
        case 10:{_a[i]._x=3*60+30;_a[i]._y=2*60+30;}
                break;
        case 9:{_a[i]._x=2*60+30;_a[i]._y=2*60+30;}
                break;
        case 8:{_a[i]._x=60+30;_a[i]._y=2*60+30;}//第二列
                break;
        case 7:{_a[i]._x=8*60+30;_a[i]._y=60+30;}
                break;
        case 6:{_a[i]._x=7*60+30;_a[i]._y=60+30;}
                break;
        case 5:{_a[i]._x=6*60+30;_a[i]._y=60+30;}
                break;
        case 4:{_a[i]._x=5*60+30;_a[i]._y=60+30;}
                break;
        case 3:{_a[i]._x=4*60+30;_a[i]._y=60+30;}
                break;
        case 2:{_a[i]._x=3*60+30;_a[i]._y=60+30;}
                break;
        case 1:{_a[i]._x=2*60+30;_a[i]._y=60+30;}
                break;
        case 0:{_a[i]._x=60+30;_a[i]._y=60+30;}//第一列
                break;
        default:;
            break;
     }
  }
}









board::~board()
{

}
