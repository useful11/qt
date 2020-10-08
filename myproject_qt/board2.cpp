#include "board2.h"
#include "ui_board2.h"
#include<QPainter>
#include<QString>
#include<QtGlobal>
#include<QTime>
#include<QDebug>
#include<QRect>
#include<QMouseEvent>
#include<QPoint>
#include <QWidget>
#include <QEventLoop>
#include<QPen>
board2::board2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::board2)
{
    ui->setupUi(this);
    q=1;//人机交换
    step=0;//记录棋子所走步数

     //固定窗口大小
     this->setFixedSize(1200,1200);
       setWindowTitle(QString("象棋暗棋比大小"));

     //棋盘格子长度
     l=80;

     //棋子大小
     r=35;

     //初始化flag
      flag1=-1;
      flag2=-1;
      flag3=-1;

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
      _a[0]._type="将";_a[0]._id=0;_a[0].str=16;
      _a[1]._type="士";_a[1]._id=1;_a[1].str=14;
      _a[2]._type="士";_a[2]._id=2;_a[2].str=14;
      _a[3]._type="象";_a[3]._id=3;_a[3].str=12;
      _a[4]._type="象";_a[4]._id=4;_a[4].str=12;
      _a[5]._type="马";_a[5]._id=5;_a[5].str=8;
      _a[6]._type="马";_a[6]._id=6;_a[6].str=8;
      _a[7]._type="车";_a[7]._id=7;_a[7].str=10;
      _a[8]._type="车";_a[8]._id=8;_a[8].str=10;
      _a[9]._type="炮";_a[9]._id=9;_a[9].str=5;
      _a[10]._type="炮";_a[10]._id=10;_a[10].str=5;
      _a[11]._type="卒";_a[11]._id=11;_a[11].str=4;
      _a[12]._type="卒";_a[12]._id=12;_a[12].str=4;
      _a[13]._type="卒";_a[13]._id=13;_a[13].str=4;
      _a[14]._type="卒";_a[14]._id=14;_a[14].str=4;
      _a[15]._type="卒";_a[15]._id=15;_a[15].str=4;

      for(int i=16;i<32;i++)
      {
          _a[i]._x=0;
          _a[i]._y=0;
          _a[i]._place=0;
          _a[i]._color=0;    //0表示红色，1表示黑色
          _a[i]._dead=0;     //0表示仍然存活，1表示被吃掉
          _a[i]._drawed=0 ;   //0表示仍未被翻面，1表示已翻面
      }
      _a[16]._type="帅";_a[16]._id=16;_a[16].str=16;
      _a[17]._type="仕";_a[17]._id=17;_a[17].str=14;
      _a[18]._type="仕";_a[18]._id=18;_a[18].str=14;
      _a[19]._type="相";_a[19]._id=19;_a[19].str=12;
      _a[20]._type="相";_a[20]._id=20;_a[20].str=12;
      _a[21]._type="马";_a[21]._id=21;_a[21].str=8;
      _a[22]._type="马";_a[22]._id=22;_a[22].str=8;
      _a[23]._type="车";_a[23]._id=23;_a[23].str=10;
      _a[24]._type="车";_a[24]._id=24;_a[24].str=10;
      _a[25]._type="炮";_a[25]._id=25;_a[25].str=5;
      _a[26]._type="炮";_a[26]._id=26;_a[26].str=5;
      _a[27]._type="兵";_a[27]._id=27;_a[27].str=4;
      _a[28]._type="兵";_a[28]._id=28;_a[28].str=4;
      _a[29]._type="兵";_a[29]._id=29;_a[29].str=4;
      _a[30]._type="兵";_a[30]._id=30;_a[30].str=4;
      _a[31]._type="兵";_a[31]._id=31;_a[31].str=4;
      //初始化完成

      //获得随机位置
      getplace();
       for(int i=0;i<32;i++)
         place_point(_a[i]._place,_a[i]._x,_a[i]._y);



 }

 void board2::paintEvent(QPaintEvent *)//显示
 {
      step=step+1;
      QPainter painter(this);
      QPen pen=painter.pen();//画笔
       pen.setWidth(3);//设置线条粗细
       painter.setPen(pen);


     //画棋盘
     //画10条横线
     for(int i=1;i<=10;i++)
        painter.drawLine(QPoint(l,i*l),QPoint(9*l,i*l));
     //画9条竖线
     for(int i=1;i<=9;i++)
        if(i==1||i==9)
           painter.drawLine(QPoint(i*l,l),QPoint(i*l,10*l));
        else
        {
            painter.drawLine(QPoint(i*l,l),QPoint(i*l,5*l));
            painter.drawLine(QPoint(i*l,6*l),QPoint(i*l,10*l));

        }

//画九宫格
painter.drawLine(QPoint(4*l,8*l),QPoint(6*l,10*l));
painter.drawLine(QPoint(4*l,10*l),QPoint(6*l,8*l));
painter.drawLine(QPoint(4*l,l),QPoint(6*l,3*l));
painter.drawLine(QPoint(4*l,3*l),QPoint(6*l,l));

     //画棋子
     painter.setFont(QFont("宋体",25,700));           //设置棋子的字体大小


       QRect rect;                                     //显示棋面的矩形
       for(int t=0;t<32;t++)                          //显示棋子
       {  rect=QRect(_a[t]._x-r,_a[t]._y-r,2*r,2*r); //每个棋子上矩形位置

           if(t==flag1)                             //改变被鼠标点中棋子的颜色
             painter.setBrush(QBrush(Qt::blue));
           else
             painter.setBrush(QBrush(Qt::yellow));


           painter.setPen(Qt::black);              //初始颜色为黑色
              painter.drawEllipse(QPoint(_a[t]._x,_a[t]._y),r,r);//画棋子边框，棋子半径为25

           if(_a[t]._color==0)                    //棋子为红色
              painter.setPen(Qt::red);
           if(_a[t]._drawed==1)                   //如果棋子翻转
             painter.drawText(rect ,_a[t].gettext(_a[t]._id),QTextOption(Qt::AlignCenter));//显示棋面

}
         bool r=rule();//判断棋局是否结束
          if(r)
            return;

//红棋
}

/*void board2::t()
{
    QTime time;
    time.start();
    while(time.elapsed()<1000)
      QCoreApplication::processEvents();
    qDebug()<<q;
    if(q==1)
    {
        v1=0;

      for(int i=16;i<32;i++)//每个红色棋子的选择
      {  A1[i][0]=-1;
          A1[i][1]=-1;
            A1[i][2]=-1;
      }

        for(int j=16;j<32;j++)//每个棋子
         if(_a[j]._drawed==1&&_a[j]._dead==0)
          {
              black1(A1,v1,_a[j]._place,j);//j是现在的操作数,i是所在的格子数
                  v1=v1+1;

          }

       if(v1!=0){
        choice(A1,v1,2);//选择出这一次的最佳移动


      int i=0;
      for(;i<v1;i++)//执行这次的最佳移动
      {
              if(A1[i][0]==0)//吃子
              {   _a[A1[i][1]]._dead=1;
                  _a[A1[i][2]]._x=_a[A1[i][1]]._x;
                  _a[A1[i][2]]._y=_a[A1[i][1]]._y;
                  _a[A1[i][2]]._place=_a[A1[i][1]]._place;
                   deadchess(_a[A1[i][1]]._id,_a[A1[i][1]]._x,_a[A1[i][1]]._y);
                   q=2;
                  break;

              }

              if(A1[i][0]==1||A1[i][0]==2)//逃跑或移动
              {
                  int x=0;
                  int y=0;
                  place_point(A1[i][1],x,y);
                  _a[A1[i][2]]._x=x;
                  _a[A1[i][2]]._y=y;
                  _a[A1[i][2]]._place=A1[i][1];
                  q=2;
                  break;

              }

          }
      if(i<v)
      repaint();

      if(i==v)//选择均是不移动，就顺序翻子
      {  int flag4=0;
          for(int j=0;j<32;j++)
            {for(int i=0;i<32;i++)
              if(_a[i]._drawed==0&&_a[i]._place==j&&_a[i]._dead==0)
                { _a[i]._drawed=1;
                  q=2;
                  flag4=1;
                  break;
                }
              if(flag4==1)
                  break;
          }
          repaint();
      }
  }
      else
      {
          int flag4=0;
          for(int j=32;j>=0;j--)
            {for(int i=0;i<32;i++)
              if(_a[i]._drawed==0&&_a[i]._place==j)
                { _a[i]._drawed=1;
                  q=2;
                  flag4=1;
                  break;
                }
              if(flag4==1)
                  break;
          }
          repaint();
      }
}
            else
            {
              for(int i=0;i<16;i++)//每个己方的棋子的选择
              {  A[i][0]=-1;
                  A[i][1]=-1;
                    A[i][2]=-1;
              }

              v=0;

                for(int j=0;j<16;j++)//每个棋子
                 if(_a[j]._drawed==1&&_a[j]._dead==0)
                  {
                      black(A,v,_a[j]._place,j);//j是现在的操作数,i是所在的格子数
                          v=v+1;

                  }

               if(v!=0){
                choice(A,v,2);//选择出这一次的最佳移动


              int i=0;
              for(;i<v;i++)//执行这次的最佳移动
              {
                      if(A[i][0]==0)//吃子
                      {   _a[A[i][1]]._dead=1;
                          _a[A[i][2]]._x=_a[A[i][1]]._x;
                          _a[A[i][2]]._y=_a[A[i][1]]._y;
                          _a[A[i][2]]._place=_a[A[i][1]]._place;
                           deadchess(_a[A[i][1]]._id,_a[A[i][1]]._x,_a[A[i][1]]._y);
                           q=1;
                          break;

                      }

                      if(A[i][0]==1||A[i][0]==2)//逃跑或移动
                      {
                          int x=0;
                          int y=0;
                          place_point(A[i][1],x,y);
                          _a[A[i][2]]._x=x;
                          _a[A[i][2]]._y=y;
                          _a[A[i][2]]._place=A[i][1];
                          q=1;
                          break;

                      }

                  }
              if(i<v)
              repaint();

              if(i==v)//选择均是不移动，就顺序翻子
              {  int flag4=0;
                  for(int j=0;j<32;j++)
                    {for(int i=0;i<32;i++)
                      if(_a[i]._drawed==0&&_a[i]._place==j&&_a[i]._dead==0)
                        { _a[i]._drawed=1;
                          q=1;
                          flag4=1;
                          break;
                        }
                      if(flag4==1)
                          break;
                  }
                  repaint();
              }
          }
              else
              {
                  int flag4=0;
                  for(int j=32;j>=0;j--)
                    {for(int i=0;i<32;i++)
                      if(_a[i]._drawed==0&&_a[i]._place==j)
                        { _a[i]._drawed=1;
                          q=1;
                          flag4=1;
                          break;
                        }
                      if(flag4==1)
                          break;
                  }
                  repaint();
              }
      }
    t();

}*/
 void board2::getplace()
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

 void board2::place_point(int a,int&x,int &y)
    {         switch (a=a+0) {
                case 31:{x=8*l+l/2;y=4*l+l/2;}
                        break;
                case 30:{x=7*l+l/2;y=4*l+l/2;}
                        break;
                case 29:{x=6*l+l/2;y=4*l+l/2;}
                        break;
                case 28:{x=5*l+l/2;y=4*l+l/2;}
                        break;
                case 27:{x=4*l+l/2;y=4*l+l/2;}
                        break;
                case 26:{x=3*l+l/2;y=4*l+l/2;}
                        break;
                case 25:{x=2*l+l/2;y=4*l+l/2;}
                        break;
                case 24:{x=l+l/2;y=4*l+l/2;}//第四列
                        break;
                case 23:{x=8*l+l/2;y=3*l+l/2;}
                        break;
                case 22:{x=7*l+l/2;y=3*l+l/2;}
                        break;
                case 21:{x=6*l+l/2;y=3*l+l/2;}
                        break;
                case 20:{x=5*l+l/2;y=3*l+l/2;}
                        break;
                case 19:{x=4*l+l/2;y=3*l+l/2;}
                        break;
                case 18:{x=3*l+l/2;y=3*l+l/2;}
                        break;
                case 17:{x=2*l+l/2;y=3*l+l/2;}
                        break;
                case 16:{x=l+l/2;y=3*l+l/2;}//第三列
                        break;
                case 15:{x=8*l+l/2;y=2*l+l/2;}
                        break;
                case 14:{x=7*l+l/2;y=2*l+l/2;}
                        break;
                case 13:{x=6*l+l/2;y=2*l+l/2;}
                        break;
                case 12:{x=5*l+l/2;y=2*l+l/2;}
                        break;
                case 11:{x=4*l+l/2;y=2*l+l/2;}
                        break;
                case 10:{x=3*l+l/2;y=2*l+l/2;}
                        break;
                case 9:{x=2*l+l/2;y=2*l+l/2;}
                        break;
                case 8:{x=l+l/2;y=2*l+l/2;}//第二列
                        break;
                case 7:{x=8*l+l/2;y=l+l/2;}
                        break;
                case 6:{x=7*l+l/2;y=l+l/2;}
                        break;
                case 5:{x=6*l+l/2;y=l+l/2;}
                        break;
                case 4:{x=5*l+l/2;y=l+l/2;}
                        break;
                case 3:{x=4*l+l/2;y=l+l/2;}
                        break;
                case 2:{x=3*l+l/2;y=l+l/2;}
                        break;
                case 1:{x=2*l+l/2;y=l+l/2;}
                        break;
                case 0:{x=l+l/2;y=l+l/2;}//第一列
                        break;
                default:;
                        break;
         }
      }

 void board2::deadchess(int a, int &x, int &y)
 {
              switch (a=a+0) {
                 case 31:{x=8*l+l/2;y=9*l+l/2;}
                         break;
                 case 30:{x=7*l+l/2;y=9*l+l/2;}
                         break;
                 case 29:{x=6*l+l/2;y=9*l+l/2;}
                         break;
                 case 28:{x=5*l+l/2;y=9*l+l/2;}
                         break;
                 case 27:{x=4*l+l/2;y=9*l+l/2;}
                         break;
                 case 26:{x=3*l+l/2;y=9*l+l/2;}
                         break;
                 case 25:{x=2*l+l/2;y=9*l+l/2;}
                         break;
                 case 24:{x=l+l/2;y=9*l+l/2;}//第四列
                         break;
                 case 23:{x=8*l+l/2;y=8*l+l/2;}
                         break;
                 case 22:{x=7*l+l/2;y=8*l+l/2;}
                         break;
                 case 21:{x=6*l+l/2;y=8*l+l/2;}
                         break;
                 case 20:{x=5*l+l/2;y=8*l+l/2;}
                         break;
                 case 19:{x=4*l+l/2;y=8*l+l/2;}
                         break;
                 case 18:{x=3*l+l/2;y=8*l+l/2;}
                         break;
                 case 17:{x=2*l+l/2;y=8*l+l/2;}
                         break;
                 case 16:{x=l+l/2;y=8*l+l/2;}//第三列
                         break;
                 case 15:{x=8*l+l/2;y=7*l+l/2;}
                         break;
                 case 14:{x=7*l+l/2;y=7*l+l/2;}
                         break;
                 case 13:{x=6*l+l/2;y=7*l+l/2;}
                         break;
                 case 12:{x=5*l+l/2;y=7*l+l/2;}
                         break;
                 case 11:{x=4*l+l/2;y=7*l+l/2;}
                         break;
                 case 10:{x=3*l+l/2;y=7*l+l/2;}
                         break;
                 case 9:{x=2*l+l/2;y=7*l+l/2;}
                         break;
                 case 8:{x=l+l/2;y=7*l+l/2;}//第二列
                         break;
                 case 7:{x=8*l+l/2;y=6*l+l/2;}
                         break;
                 case 6:{x=7*l+l/2;y=6*l+l/2;}
                         break;
                 case 5:{x=6*l+l/2;y=6*l+l/2;}
                         break;
                 case 4:{x=5*l+l/2;y=6*l+l/2;}
                         break;
                 case 3:{x=4*l+l/2;y=6*l+l/2;}
                         break;
                 case 2:{x=3*l+l/2;y=6*l+l/2;}
                         break;
                 case 1:{x=2*l+l/2;y=6*l+l/2;}
                         break;
                 case 0:{x=l+l/2;y=6*l+l/2;}//第一列
                         break;
                 default:;
                         break;
          }
}


void board2:: black(int b[][3],int o,int w,int k)//w为当前棋子所在格子数，k为当前操作的棋子序号,o为当前A数组的序号
{
  int m[4][3]={-1};

   int q=w%8;//列

     int p=w/8;//行

     if(_a[k]._type!="炮")
{      result(m,(p-1),q,0,k);
       result(m,(p+1),q,1,k);
        result(m,p,(q+1),2,k);
         result(m,p,(q-1),3,k);

           for(int n=0;n<4;n++)
               if(m[n][0]==2)
               {   int m1[4][3]={-1};
                   int a=m[n][2]%8;
                   int b=m[n][2]/8;
                   result(m1,(b-1),a,0,k);
                       result(m1,(b+1),a,1,k);
                          result(m1,b,(a+1),2,k);
                            result(m1,b,(a-1),3,k);
                   for(int e=0;e<4;e++)
                   {
                       if(m1[e][0]==1)
                          { m[n][0]=-1;
                           m[n][1]=-1;
                           m[n][2]=-1;
                           break;
                       }
                   }

               } choice(m, 4,1);
}       else
        { result1(m,w,k);
         choice(m,4,1);
        }

   for(int i=0;i<4;i++)
   {
       if(m[i][0]!=-1)
        {
           b[o][0]=m[i][0];
            b[o][1]=m[i][1];
             b[o][2]=m[i][2];
             break;
        }

    }
}


void board2:: black1(int b[][3],int o,int w,int k)//w为当前棋子所在格子数，k为当前操作的棋子序号,o为当前A数组的序号
{
  int m[4][3]={-1};

   int q=w%8;//列

     int p=w/8;//行

     if(_a[k]._type!="炮")
{      result2(m,(p-1),q,0,k);
       result2(m,(p+1),q,1,k);
        result2(m,p,(q+1),2,k);
         result2(m,p,(q-1),3,k);

             choice(m, 4,1);  }
       else
        { result3(m,w,k);
         choice(m,4,1);
        }

   for(int i=0;i<4;i++)
   {
       if(m[i][0]!=-1)
        {
           b[o][0]=m[i][0];
            b[o][1]=m[i][1];
             b[o][2]=m[i][2];
             break;
        }

    }
}


void board2::choice(int a[][3],int n,int h)
{   int flag11=-2;
  int flag12=-2;
  int flag13=-2;
  int flag21=-2;
  int flag22=-2;
  int flag23=-2;
int i=0;
int y=-2;
int u=-2;

if(h==1){
  for(int j=0;j<4;j++)//找到是否有移动的情况
  {
      if(a[j][0]==2)
      {
          y=a[j][1];//移动到的位置
          u=j;//移动情况的序号
          break;
      }
  }

  if(u!=-2)//有移动情况就把不移动情况去除
  {  for(int j=0;j<4;j++)
       if(a[j][0]==4)
         a[j][0]=-1;
  }

//
  for(;i<4;i++)
    {
      if(a[i][0]==0&&flag11==-2)//第一次遇到吃子的情况
        { flag11=a[i][1];//所吃子的序号
            flag12=i;//吃子情况的序号
             continue;
        }

      if(a[i][0]==0&&flag11!=-2)//判断哪种吃子情况
         { flag13=a[i][1];//被吃者
            if(_a[flag13].str>_a[flag11].str)
              {

                a[flag12][0]=-1;
                  a[flag12][1]=-1;
                   a[flag12][2]=-1;
                    flag11=flag13;
                      flag12=i;
                       continue;


              }
            else
            {
                a[i][0]=-1;
                  a[i][1]=-1;
                   a[i][2]=-1;
                    continue;

            }
       }

      if(a[i][0]==1)//逃跑的情况
        { if(u==-2)//无移动情况，逃跑置-1
             {
              a[i][0]=-1;
              a[i][1]=-1;
              a[i][2]=-1;
              continue;

             }
          else
              if(flag21==-3)
              {
                  a[i][0]=-1;
                  a[i][1]=-1;
                  a[i][2]=-1;
                  continue;
              }

              else
            { flag22=i;
              flag21=-3;
              a[i][1]=y;
              a[u][0]=-1;//移动情况置-1
              a[u][1]=-1;
              a[u][2]=-1;

              continue;
            }
        }


      if(a[i][0]==1&&flag12!=-2)//逃走和吃子都有，选吃子
      {

                a[i][0]=-1;
                 a[i][1]=-1;
                  a[i][2]=-1;
                   flag21=-2;
                    flag22=-2;
                     continue;


       }
      if(a[i][0]==0&&flag22!=-2)//逃走和吃子都有，选吃子
      {
          a[flag22][0]=-1;
           a[flag22][1]=-1;
            a[flag22][2]=-1;
             flag21=-2;
              flag22=-2;
               continue;
      }
}
//
  for(int j=0;j<4;j++)
  {if(flag12!=-2)
      {
      for(int j=0;j<4;j++)
      {
          if(j!=flag12)
          {
              a[j][0]=-1;
              a[j][1]=-1;
              a[j][2]=-1;

          }
      }
      u=-2;
      y=-2;
      continue;
      }


  if(flag22!=-2)
      {
      for(int j=0;j<4;j++)
      {
          if(j!=flag22)
          {
              a[j][0]=-1;
              a[j][1]=-1;
              a[j][2]=-1;
          }
      }
      u=-2;
      y=-2;
     continue;
      }

  if(u!=-2&&flag12==-2&&flag22==-2)
  { for(int j=0;j<4;j++)
       if(j!=u)
       {
           a[j][0]=-1;
           a[j][1]=-1;
           a[j][2]=-1;
       }
      continue;
     }
  }

}

else
{
    for(;i<n;i++)
      {
        if(a[i][0]==0&&flag11==-2)//第一次遇到吃子的情况，清除所有不移动和移动的选择
          { flag11=a[i][1];//所吃子的序号
              flag12=i;//吃子情况的序号
            for(int j=0;j<n;j++)//清除
               if(a[j][0]==4||a[j][0]==2)
             {
                    a[j][0]=-1;
                    a[j][1]=-1;
                    a[j][2]=-1;

             }
            continue;
          }

        if(a[i][0]==1&&flag21==-2)//第一次遇到逃跑的情况，清除所有不移动和移动的选择
          { flag21=a[i][2];//被吃者序号
             flag22=i;
            for(int j=0;j<n;j++)//清除
               if(a[j][0]==4||a[j][0]==2)
             {
                    a[j][0]=-1;
                    a[j][1]=-1;
                    a[j][2]=-1;

             }
            continue;
          }

        if(a[i][0]==1&&flag21!=-2)//判断哪种逃跑情况
           { flag23=a[i][2];//被吃者
              if(_a[flag23].str>=_a[flag21].str)//让flag23逃跑
                {

                  a[flag22][0]=-1;
                    a[flag22][1]=-1;
                     a[flag22][2]=-1;
                        flag22=i;
                         flag21=flag23;

                         continue;
                }
              else
              {
                  a[i][0]=-1;
                    a[i][1]=-1;
                     a[i][2]=-1;
                       continue;
              }
         }


         if(a[i][0]==0&&flag11!=-2)//判断哪种吃子情况
            { flag13=a[i][1];//被吃者
               if(_a[flag13].str>_a[flag11].str)
                 {

                   a[flag12][0]=-1;
                     a[flag12][1]=-1;
                      a[flag12][2]=-1;
                       flag11=flag13;
                         flag12=i;
                           continue;
                 }
               else
               {
                   a[i][0]=-1;
                     a[i][1]=-1;
                      a[i][2]=-1;
                       continue;

               }

          }

        }


    if(step%2==0)
    {i=0;
   for(;i<n;i++)
   { if((a[i][0]==1&&flag12!=-2)||(a[i][0]==0&&flag22!=-2))
      {  if(_a[flag11].str>_a[flag21].str)//吃子
        {
            a[flag22][0]=-1;
            a[flag22][1]=-1;
            a[flag22][2]=-1;
            flag21=-2;
            flag22=-2;
              continue;
        }

        else//逃跑
        {
            a[flag12][0]=-1;
            a[flag12][1]=-1;
            a[flag12][2]=-1;
            flag11=-2;
            flag12=-2;
            continue;
        }
}
      if(a[i][0]==2&&flag22==-2&&flag12==-2)//移动
      {
          for(int j=0;j<n;j++)
             if(j!=i)
             {
                 a[j][0]=-1;
                 a[j][1]=-1;
                 a[j][2]=-1;
             }
        }

      }
  }
    else
    {   i=n-1;
        for(;i>=0;i--)
        { if((a[i][0]==1&&flag12!=-2)||(a[i][0]==0&&flag22!=-2))
            { if(_a[flag11].str>_a[flag21].str)//吃子
             {
                 a[flag22][0]=-1;
                 a[flag22][1]=-1;
                 a[flag22][2]=-1;
                 flag21=-2;
                 flag22=-2;
                   continue;
             }

             else//逃跑
             {
                 a[flag12][0]=-1;
                 a[flag12][1]=-1;
                 a[flag12][2]=-1;
                 flag11=-2;
                 flag12=-2;
                 continue;
                   //qDebug()<<66;
             }
         }
           if(a[i][0]==2&&flag22==-2&&flag12==-2)//移动
           {
               for(int j=0;j<n;j++)
                  if(j!=i)
                  {
                      a[j][0]=-1;
                      a[j][1]=-1;
                      a[j][2]=-1;
                  }
             }

          }
    }
}

i=0;
for(;i<n;i++)
  if(a[i][0]==4)
    a[i][0]=-1;
}

void board2:: result(int m[][3], int a,int b,int c,int d)//a代表行，b代表列，c代表数组序号，d代表当前己方的操作对象序号
{  int B=a*8+b;
   int i=0;
     if(a>=0&&a<=3&&b>=0&&b<=7)
          {   for(;i<32;i++)//遍历棋子
            {
             //不移动                 /*黑棋*/         /*已翻面*/                                                                                   /*红棋*/              /*等于马、兵、卒的红棋*/
           if((_a[i]._place==B&&_a[i]._color==1&&_a[i]._drawed==1&&_a[i]._dead==0)||(_a[i]._drawed==0&&_a[i]._place==B&&_a[i]._dead==0)||(_a[i]._place==B&&_a[i]._dead==0&&_a[i]._drawed==1&&_a[i]._color==0&&((_a[i]._type=="马"&&_a[d]._type=="马")||(_a[d]._type=="卒"&&_a[i]._type=="兵"))))
           {
               m[c][0]=4;
                 m[c][1]=-1;
                   m[c][2]=-1;
                     break;
           }

           //除炮以外的棋子吃子
           if(_a[i]._place==B&&_a[i]._color==0&&((_a[i].str<=_a[d].str&&((_a[d]._type=="将"&&_a[i]._type!="兵")||_a[d]._type!="将"))||(_a[d]._type=="卒"&&_a[i]._type=="帅"))&&_a[i]._drawed==1&&_a[i]._dead==0)
            {
               m[c][0]=0;
                 m[c][1]=i;
                   m[c][2]=d;
                     break;
           }

           //逃走
           if(_a[i]._place==B&&_a[i]._drawed==1&&_a[i]._color==0&&(_a[i].str>_a[d].str||(_a[d]._type=="将"&&_a[i]._type=="兵"))&&_a[i]._dead==0)
              {
               m[c][0]=1;
                 m[c][1]=-1;
                   m[c][2]=d;
                     break;
              }
           }

         //移动
         if(i==32)
         {
             m[c][0]=2;
               m[c][1]=B;
                 m[c][2]=d;
         }
}

 else
   {
            m[c][0]=-1;
            m[c][1]=-1;
            m[c][2]=-1;

   }

}

void board2:: result2(int m[][3], int a,int b,int c,int d)//a代表行，b代表列，c代表数组序号，d代表当前己方的操作对象序号
{  int B=a*8+b;
   int i=0;
     if(a>=0&&a<=3&&b>=0&&b<=7)
          {   for(;i<32;i++)//遍历棋子
            {
             //不移动                 /*红棋*/         /*已翻面*/                                                                                   /*红棋*/              /*等于马、兵、卒的黑棋*/
           if((_a[i]._place==B&&_a[i]._color==0&&_a[i]._drawed==1&&_a[i]._dead==0)||(_a[i]._drawed==0&&_a[i]._place==B&&_a[i]._dead==0)||(_a[i]._place==B&&_a[i]._dead==0&&_a[i]._drawed==1&&_a[i]._color==1&&((_a[i]._type=="马"&&_a[d]._type=="马")||(_a[d]._type=="兵"&&_a[i]._type=="卒"))))
           {
               m[c][0]=4;
                 m[c][1]=-1;
                   m[c][2]=-1;
                     break;
           }

           //除炮以外的棋子吃子
           if(_a[i]._place==B&&_a[i]._color==1&&((_a[i].str<=_a[d].str&&((_a[d]._type=="帅"&&_a[i]._type!="卒")||_a[d]._type!="帅"))||(_a[d]._type=="卒"&&_a[i]._type=="帅"))&&_a[i]._drawed==1&&_a[i]._dead==0)
            {
               m[c][0]=0;
                 m[c][1]=i;
                   m[c][2]=d;
                     break;
           }

           //逃走
           if(_a[i]._place==B&&_a[i]._drawed==1&&_a[i]._color==1&&(_a[i].str>_a[d].str||(_a[d]._type=="帅"&&_a[i]._type=="卒"))&&_a[i]._dead==0)
              {
               m[c][0]=1;
                 m[c][1]=-1;
                   m[c][2]=d;
                     break;
              }
           }

         //移动
         if(i==32)
         {
             m[c][0]=2;
               m[c][1]=B;
                 m[c][2]=d;
         }
}

 else
   {
            m[c][0]=-1;
            m[c][1]=-1;
            m[c][2]=-1;

   }

}

void board2::result1(int b[][3],int a,int e)//A代表该棋子情况，a代表炮所在的格子,e代表操作数序号
{
  int q=a%8;//列数
  int p=a/8;//行数
  int t=0;//次数
  int flag4=-2;
  int flag5=-2;
  int flag6=-2;
  int flag7=-2;
  for(int i=1;(q+i)<=7;i++)
  {flag7=-1;
    for(int j=0;j<32;j++)
  {  if(_a[j]._place==(p*8+q+i)&&_a[j]._dead==0)
           { t=t+1;

           }
      if(i==1&&_a[j]._place==(p*8+q+i)&&_a[j]._dead==0)
        flag4=-1;

      if(i==1&&_a[j]._place==(p*8+q+i)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="兵"&&_a[j]._type!="炮")&&_a[j]._color==0)
        flag6=-1;



       if(_a[j]._place==(p*8+q+i)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==0&&_a[j]._type!="马")
         flag5=j;
   }
}


  if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
    { b[0][0]=2;
      b[0][1]=p*8+q+1;
       b[0][2]=e;
    }

   else
      if(flag5!=-2)//吃子
   {
       b[0][0]=0;
        b[0][1]=flag5;
         b[0][2]=e;
   }

      else
          if(flag6!=-2)
          {
              b[0][0]=1;
              b[0][1]=-1;
               b[0][2]=e;
          }
          else
          {
              b[0][0]=-1;
              b[0][1]=-1;
               b[0][2]=-1;
          }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;
for(int i=1;(q-i)>=0;i++)
{flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==(p*8+q-i)&&_a[j]._dead==0)
    {t=t+1;

    }
  if(i==1&&_a[j]._place==(p*8+q-i)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==(p*8+q-i)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="兵"&&_a[j]._type!="炮")&&_a[j]._color==0)
    flag6=-1;


   if(_a[j]._place==(p*8+q-i)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==0&&_a[j]._type!="马")
     flag5=j;
}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[1][0]=2;
  b[1][1]=p*8+q-1;
   b[1][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[1][0]=0;
    b[1][1]=flag5;
     b[1][2]=e;
}

  else
      if(flag6!=-2)//逃跑
      {
          b[1][0]=1;
          b[1][1]=-1;
           b[1][2]=e;
      }
      else
      {
          b[1][0]=-1;
          b[1][1]=-1;
           b[1][2]=-1;
      }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;

for(int i=1;(p+i)<=3;i++)
{   flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0)
       { t=t+1;

       }
  if(i==1&&_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="兵"&&_a[j]._type!="炮")&&_a[j]._color==0)
    flag6=-1;



   if(_a[j]._place==((p+i)*8+q)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==0&&_a[j]._type!="马")
     flag5=j;

}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[2][0]=2;
  b[2][1]=((p+1)*8+q);
   b[2][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[2][0]=0;
    b[2][1]=flag5;
     b[2][2]=e;
}

  else
      if(flag6!=-2)
      {
          b[2][0]=1;
          b[2][1]=-1;
           b[2][2]=e;
      }
      else
      {
          b[2][0]=-1;
          b[2][1]=-1;
           b[2][2]=-1;
      }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;
for(int i=1;(p-i)>=0;i++)
{flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0)
    {t=t+1;

    }

  if(i==1&&_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="兵"&&_a[j]._type!="炮")&&_a[j]._color==0)
    flag6=-1;


   if(_a[j]._place==((p-i)*8+q)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==0&&_a[j]._type!="马")
     flag5=j;

}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[3][0]=2;
  b[3][1]=((p-1)*8+q);
   b[3][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[3][0]=0;
    b[3][1]=flag5;
     b[3][2]=e;
}

  else
      if(flag6!=-2)
      {
          b[3][0]=1;
          b[3][1]=-1;
           b[3][2]=e;
      }
      else
      {
          b[3][0]=-1;
          b[3][1]=-1;
           b[3][2]=-1;
      }

}
void board2::result3(int b[][3],int a,int e)//A代表该棋子情况，a代表炮所在的格子,e代表操作数序号
{
  int q=a%8;//列数
  int p=a/8;//行数
  int t=0;//次数
  int flag4=-2;
  int flag5=-2;
  int flag6=-2;
  int flag7=-2;
  for(int i=1;(q+i)<=7;i++)
  {flag7=-1;
    for(int j=0;j<32;j++)
  {  if(_a[j]._place==(p*8+q+i)&&_a[j]._dead==0)
           { t=t+1;

           }
      if(i==1&&_a[j]._place==(p*8+q+i)&&_a[j]._dead==0)
        flag4=-1;

      if(i==1&&_a[j]._place==(p*8+q+i)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="卒"&&_a[j]._type!="炮")&&_a[j]._color==1)
        flag6=-1;



       if(_a[j]._place==(p*8+q+i)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==1&&_a[j]._type!="马")
         flag5=j;
   }
}


  if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
    { b[0][0]=2;
      b[0][1]=p*8+q+1;
       b[0][2]=e;
    }

   else
      if(flag5!=-2)//吃子
   {
       b[0][0]=0;
        b[0][1]=flag5;
         b[0][2]=e;
   }

      else
          if(flag6!=-2)
          {
              b[0][0]=1;
              b[0][1]=-1;
               b[0][2]=e;
          }
          else
          {
              b[0][0]=-1;
              b[0][1]=-1;
               b[0][2]=-1;
          }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;
for(int i=1;(q-i)>=0;i++)
{flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==(p*8+q-i)&&_a[j]._dead==0)
    {t=t+1;

    }
  if(i==1&&_a[j]._place==(p*8+q-i)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==(p*8+q-i)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="卒"&&_a[j]._type!="炮")&&_a[j]._color==1)
    flag6=-1;


   if(_a[j]._place==(p*8+q-i)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==1&&_a[j]._type!="马")
     flag5=j;
}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[1][0]=2;
  b[1][1]=p*8+q-1;
   b[1][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[1][0]=0;
    b[1][1]=flag5;
     b[1][2]=e;
}

  else
      if(flag6!=-2)//逃跑
      {
          b[1][0]=1;
          b[1][1]=-1;
           b[1][2]=e;
      }
      else
      {
          b[1][0]=-1;
          b[1][1]=-1;
           b[1][2]=-1;
      }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;

for(int i=1;(p+i)<=3;i++)
{   flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0)
       { t=t+1;

       }
  if(i==1&&_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==((p+i)*8+q)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="卒"&&_a[j]._type!="炮")&&_a[j]._color==1)
    flag6=-1;



   if(_a[j]._place==((p+i)*8+q)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==1&&_a[j]._type!="马")
     flag5=j;

}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[2][0]=2;
  b[2][1]=((p+1)*8+q);
   b[2][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[2][0]=0;
    b[2][1]=flag5;
     b[2][2]=e;
}

  else
      if(flag6!=-2)
      {
          b[2][0]=1;
          b[2][1]=-1;
           b[2][2]=e;
      }
      else
      {
          b[2][0]=-1;
          b[2][1]=-1;
           b[2][2]=-1;
      }
t=0;
flag4=-2;
flag5=-2;
flag6=-2;
flag7=-2;
for(int i=1;(p-i)>=0;i++)
{flag7=-1;
for(int j=0;j<32;j++)
{ if(_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0)
    {t=t+1;

    }

  if(i==1&&_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0)
    flag4=-1;

  if(i==1&&_a[j]._place==((p-i)*8+q)&&_a[j]._dead==0&&_a[j]._drawed==1&&(_a[j]._type!="卒"&&_a[j]._type!="炮")&&_a[j]._color==1)
    flag6=-1;


   if(_a[j]._place==((p-i)*8+q)&&t==2&&_a[j]._dead==0&&_a[j]._drawed==1&&_a[j]._color==1&&_a[j]._type!="马")
     flag5=j;

}
}

if(((t==0&&flag7!=-2)||(t!=0&&flag4==-2))&&flag5==-2)//移动
{ b[3][0]=2;
  b[3][1]=((p-1)*8+q);
   b[3][2]=e;
}

else
  if(flag5!=-2)//吃子
{
   b[3][0]=0;
    b[3][1]=flag5;
     b[3][2]=e;
}

  else
      if(flag6!=-2)
      {
          b[3][0]=1;
          b[3][1]=-1;
           b[3][2]=e;
      }
      else
      {
          b[3][0]=-1;
          b[3][1]=-1;
           b[3][2]=-1;
      }

}

bool board2::rule()
{
  int t1=0;
   int t2=0;
  for(int i=0;i<32;i++)
    {if(_a[i]._color==1&&_a[i]._dead==1&&_a[i]._drawed==1)
        t1=t1+1;
     if(_a[i]._color==0&&_a[i]._dead==1&&_a[i]._drawed==1)
         t2=t2+1;
    }
  if(t1==16)
  {
     // p3.setText(QString("红方胜"));
      return true;
  }
  if(t2==16)
  {
     // p3.setText(QString("黑方胜"));
      return true;
  }

  return false;
}





board2::~board2()
{
    delete ui;
}
