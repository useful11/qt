#include "boar.h"
#include "ui_board.h"
#include<QPainter>
#include<QString>
#include<QtGlobal>
#include<QTime>
#include<QDebug>
#include<QRect>
#include<QMouseEvent>
#include<QPoint>
#include <QWidget>
board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);
    p1.setText(QString("红方认输"));
    p1.resize(80,50);
    p1.move(880,80);
    p1.setParent(this);

    p2.setText(QString("黑方认输"));
    p2.resize(120,50);
    p2.move(880,240);
    p2.setParent(this);

    //固定窗口大小
       this->setFixedSize(1200,1200);

       //棋盘格子长度
       l=80;

       //棋子大小
       r=30;

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

        //获得随机位置
        getplace();
         for(int i=0;i<32;i++)
           place_point(_a[i]._place,_a[i]._x,_a[i]._y);

   }

   void board::paintEvent(QPaintEvent *)
   {
       QPainter painter(this);
       //画棋盘
       //画10条横线
       for(int i=1;i<=10;i++)
          painter.drawLine(QPoint(l,i*l),QPoint(9*l,i*l));
       //画9条竖线
       for(int i=1;i<=9;i++)
          if(i==1||i==9)
             painter.drawLine(QPoint(i*l,l),QPoint(i*l,10*l));
          else
          { painter.drawLine(QPoint(i*l,l),QPoint(i*l,5*l));
            painter.drawLine(QPoint(i*l,6*l),QPoint(i*l,10*l));

          }

       //画棋子
       painter.setFont(QFont("system",25,700));           //设置棋子的字体大小

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

   }


   void board::mouseReleaseEvent(QMouseEvent *ev)
   {
     QPoint pt=ev->pos();
     int x=pt.x();
     int y=pt.y();
      flag3=mousepres2(x,y);

     if(flag3==-1)                              //鼠标未点击到正确位置
         return;
     else{                                  //鼠标点到正确位置
     if(flag2==-1)
     {
          bool ifmousepress=mousepres1(flag3);//判断鼠标点击的位置是否有某个棋子上,如果在棋子上，flag3变为该棋子序号，如果没有，flag3为棋格序号
          if(ifmousepress&&_a[flag3]._drawed==0)
                _a[flag3]._drawed=1;
          else
             if(ifmousepress&&_a[flag3]._drawed==1)
              {
                 flag1=flag3;
                   flag2=flag3;
              }
            if(!ifmousepress)
            {
                return;
            }
            repaint();
     }

     else{

       bool ifmousepress=mousepres1(flag3);//判断鼠标点击的位置是否有某个棋子上
       int pao=ifpao(ifmousepress,flag2,flag3);
       bool process=rightprocess(ifmousepress,pao,flag3,flag2);//判断走棋是否合法
       bool geti=getit(pao,flag2,flag3);

         if(!ifmousepress&&process)//空格移动
           {place_point(flag3,x,y);
             _a[flag2]._x=x;
             _a[flag2]._y=y;
              _a[flag2]._place=flag3;
                flag2=-1;
                  flag1=-1;
                  repaint();
            }

          if(ifmousepress&&_a[flag3]._drawed==1&&_a[flag3]._color==_a[flag2]._color&&flag2==flag3)//单击选棋，再点击取消选棋
          {
              flag1=-1;
                flag2=-1;
                  flag3=-1;
                  repaint();

          }

          if(ifmousepress&&_a[flag3]._drawed==1&&_a[flag3]._color==_a[flag2]._color&&flag2!=flag3)//选择自己的棋子
          {
              flag1=flag3;
                flag2=flag3;
                  repaint();
          }

          if(ifmousepress&&process&&geti&&_a[flag3]._drawed==1&&_a[flag3]._color!=_a[flag2]._color)//吃子情况
          {
                     _a[flag3]._dead=1;
                       _a[flag2]._x=_a[flag3]._x;
                         _a[flag2]._y=_a[flag3]._y;
                          _a[flag2]._place=_a[flag3]._place;
                            deadchess(_a[flag3]._id,_a[flag3]._x,_a[flag3]._y);
                             flag2=-1;
                              flag1=-1;
                                  repaint();




          }
          if(ifmousepress&&_a[flag3]._drawed==0)
           {
                       return;
           }

   }

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

   void board::place_point(int a,int&x,int &y)
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

   bool board::mousepres1(int &a)
   {   int i;
       for(i=0;i<32;i++)
         if(a==_a[i]._place&&_a[i]._dead==0)
           {
                a=i;
                 break;
            }

       if(i<32)
         return true;
       else
         return false;
   }

   int board::mousepres2(int x, int y)
   {  if(y>l&&y<2*l)
      {
       if(x>l&&x<2*l)
        return 0;
      if(x>2*l&&x<3*l)
        return 1;
      if(x>3*l&&x<4*l)
        return 2;
      if(x>4*l&&x<5*l)
        return 3;
      if(x>5*l&&x<6*l)
        return 4;
      if(x>6*l&&x<7*l)
        return 5;
      if(x>7*l&&x<8*l)
        return 6;
      if(x>8*l&&x<9*l)
        return 7;
       }
       if(y>2*l&&y<3*l)
       {
      if(x>l&&x<2*l)
        return 8;
      if(x>2*l&&x<3*l)
        return 9;
      if(x>3*l&&x<4*l)
        return 10;
      if(x>4*l&&x<5*l)
        return 11;
      if(x>5*l&&x<6*l)
        return 12;
      if(x>6*l&&x<7*l)
        return 13;
      if(x>7*l&&x<8*l)
        return 14;
      if(x>8*l&&x<9*l)
        return 15;
       }
       if(y>3*l&&y<4*l)
       {
      if(x>l&&x<2*l)
        return 16;
      if(x>2*l&&x<3*l)
        return 17;
      if(x>3*l&&x<4*l)
        return 18;
      if(x>4*l&&x<5*l)
        return 19;
      if(x>5*l&&x<6*l)
        return 20;
      if(x>6*l&&x<7*l)
        return 21;
      if(x>7*l&&x<8*l)
        return 22;
      if(x>8*l&&x<9*l)
        return 23;
       }
       if(y>4*l&&y<5*l)
       {
      if(x>l&&x<2*l)
        return 24;
      if(x>2*l&&x<3*l)
        return 25;
      if(x>3*l&&x<4*l)
        return 26;
      if(x>4*l&&x<5*l)
        return 27;
      if(x>5*l&&x<6*l)
        return 28;
      if(x>6*l&&x<7*l)
        return 29;
      if(x>7*l&&x<8*l)
        return 30;
      if(x>8*l&&x<9*l)
        return 31;
      }

      return -1;
   }

   bool board::rightprocess(bool a,int b,int x,int y)//y为flag2,x为flag3
   {
       if(a)
       {  if(_a[y]._type=="炮")
            //if(b==2&&(((_a[x]._place-_a[y]._place)>0)&&((_a[x]._place-_a[y]._place)<=7))||(((_a[x]._place-_a[y]._place)<0)&&((_a[x]._place-_a[y]._place)>=-7))||
            //((_a[x]._place-_a[y]._place)==8)||((_a[x]._place-_a[y]._place)==16)||((_a[x]._place-_a[y]._place)==-8)||((_a[x]._place-_a[y]._place)==-16))
            if(b==2)
               return true;
             else
               return false;

            if(_a[y]._type!="炮")
              if(((_a[x]._place-_a[y]._place)==1)||((_a[x]._place-_a[y]._place)==-1)||((_a[x]._place-_a[y]._place)==8)||((_a[x]._place-_a[y]._place)==-8))
                return true;
              else
                return false;
       }

       if(!a)
        {
          int h=0;
           int z=0;
              place_point(x,h,z);
              if(_a[y]._type=="炮")
                //if((b==1||b==3)&&((((h-_a[y]._x)==0)&&((z-_a[y]._y)!=0))||(((h-_a[y]._x)!=0)&&((z-_a[y]._y)==0))))
                if(b==3)
                  return true;
                else
                  return false;

              if(_a[y]._type!="炮")
                if(((((h-_a[y]._x)==l)||((h-_a[y]._x)==-l))&&((z-_a[y]._y)==0))||(((h-_a[y]._x)==0)&&(((z-_a[y]._y)==-l)||((z-_a[y]._y)==l))))
                    return true;
                else
                    return false;
       }


     }

   bool board::getit( int a,int x,int y)
   {  if(_a[x]._color!=_a[y]._color)
       {
      if(_a[x]._type=="帅"||_a[x]._type=="将")
      if((_a[x]._type=="帅"&&_a[y]._type=="卒")||(_a[x]._type=="将"&&_a[y]._type=="兵"))
        return false;
      else
        return true;

      if(_a[x]._type=="仕"||_a[x]._type=="士")
      if((_a[x]._type=="仕"&&_a[y]._type=="将")||(_a[x]._type=="士"&&_a[y]._type=="帅"))
          return false;
      else
        return true;

      if(_a[x]._type=="象"||_a[x]._type=="相")
      if((_a[x]._type=="相"&&_a[y]._type=="将")||(_a[x]._type=="相"&&_a[y]._type=="士")||(_a[x]._type=="象"&&_a[y]._type=="帅")||(_a[x]._type=="象"&&_a[y]._type=="仕"))
          return false;
      else
        return true;

      if(_a[x]._type=="车")
      if((_a[x]._type=="车"&&_a[y]._type=="炮")||(_a[x]._type=="车"&&_a[y]._type=="卒")||(_a[x]._type=="车"&&_a[y]._type=="兵")||(_a[x]._type=="车"&&_a[y]._type=="马")||(_a[x]._type=="车"&&_a[y]._type=="车"))
          return true;
      else
        return false;

      if(_a[x]._type=="马")
      if((_a[x]._type=="马"&&_a[y]._type=="炮")||(_a[x]._type=="马"&&_a[y]._type=="卒")||(_a[x]._type=="马"&&_a[y]._type=="兵"))
          return true;
      else
        return false;

      if(_a[x]._type=="卒"||_a[x]._type=="兵")
      if((_a[x]._type=="卒"&&_a[y]._type=="帅")||(_a[x]._type=="兵"&&_a[y]._type=="将"))
          return true;
      else
        return false;

      if(_a[x]._type=="炮")
      if((a==2)&&_a[y]._type!="马")
          return true;
      else
        return false;

       }
       return false;
   }


   int board::ifpao(bool a, int x, int y)
   {  if(_a[x]._type!="炮")
        return 0;
      else{
       int t=0;
       if(a){
         t=pao_useed(_a[x]._place,_a[y]._place);
          }
       else
       {
         t=pao_useed(_a[x]._place,y);

       }

          switch(t+=0)
          {
           case 2:return 2;
           case 3:return 3;
           case 4:return 4;
           case 5:return 5;
          }
       }
   }
   int board::pao_useed(int x, int y)//2表示炮符合吃子条件；3表示炮与点中的位置之间无其他棋子，4表示炮与点中位置相隔两个及以上的棋子,5表示两颗棋子不在同一行列
   {  int a,b,a1,b1;
       a=x%8;//x所在的列
         b=x/8;//x所在的行
          a1=y%8;//y所在的列
           b1=y/8;//y所在的行

       int max,min;
       int t=0;
       if((a==a1&&b>b1)||(b==b1&&a>a1))
         {
           max=x;
              min=y;
         }
        else
          if((a==a1&&b<b1)||(b==b1&&a<a1))
         {
           max=y;
            min=x;
         }
           else
           return 5;

        if(a==a1)
        for(int i=min+8;i<max;i=i+8)
           for(int j=0;j<32;j++)
              if(_a[j]._place==i&&_a[j]._dead==0)
              {
                  t=t+1;

              }
        if(b==b1)
        for(int i=min+1;i<max;i++)
          for(int j=0;j<32;j++)
             if(_a[j]._place==i&&_a[j]._dead==0)
              {
                 t=t+1;

               }

         if(t==1)
             return 2;
         else
             if(t==0)
               return 3;
             else
               return 4;
   }

   void board::deadchess(int a, int &x, int &y)
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

board::~board()
{
    delete ui;
}
