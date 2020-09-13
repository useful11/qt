#include "cvsc.h"
#include "ches.h"
CvsC::CvsC(QWidget *parent) : QWidget(parent)
{

   /* //初始化每一个棋子
           for(int i=0;i<16;i++)
           {
               _b[i]._x=0;
               _b[i]._y=0;
               _b[i]._place=0;
               _b[i]._color=1;    //0表示红色，1表示黑色
               _b[i]._dead=0;     //0表示仍然存活，1表示被吃掉
               _b[i]._drawed=0;   //0表示仍未被翻面，1表示已翻面

           }
           _b[0]._type="将";_b[0]._id=0;
           _b[1]._type="士";_b[1]._id=1;
           _b[2]._type="士";_b[2]._id=2;
           _b[3]._type="象";_b[3]._id=3;
           _b[4]._type="象";_b[4]._id=4;
           _b[5]._type="马";_b[5]._id=5;
           _b[6]._type="马";_b[6]._id=6;
           _b[7]._type="车";_b[7]._id=7;
           _b[8]._type="车";_b[8]._id=8;
           _b[9]._type="炮";_b[9]._id=9;
           _b[10]._type="炮";_b[10]._id=10;
           _b[11]._type="卒";_b[11]._id=11;
           _b[12]._type="卒";_b[12]._id=12;
           _b[13]._type="卒";_b[13]._id=13;
           _b[14]._type="卒";_b[14]._id=14;
           _b[15]._type="卒";_b[15]._id=15;

           for(int i=16;i<32;i++)
           {
               _b[i]._x=0;
               _b[i]._y=0;
               _b[i]._place=0;
               _b[i]._color=0;    //0表示红色，1表示黑色
               _b[i]._dead=0;     //0表示仍然存活，1表示被吃掉
               _b[i]._drawed=0 ;   //0表示仍未被翻面，1表示已翻面
           }
           _b[16]._type="帅";_b[16]._id=16;
           _b[17]._type="仕";_b[17]._id=17;
           _b[18]._type="仕";_b[18]._id=18;
           _b[19]._type="相";_b[19]._id=19;
           _b[20]._type="相";_b[20]._id=20;
           _b[21]._type="马";_b[21]._id=21;
           _b[22]._type="马";_b[22]._id=22;
           _b[23]._type="车";_b[23]._id=23;
           _b[24]._type="车";_b[24]._id=24;
           _b[25]._type="炮";_b[25]._id=25;
           _b[26]._type="炮";_b[26]._id=26;
           _b[27]._type="兵";_b[27]._id=27;
           _b[28]._type="兵";_b[28]._id=28;


  }

A[32][3]={-1};//每个己方的棋子的选择
int v=0;
for(int i=0;i<32;i++)
 for(int j=0;j<16;j++)//每个棋子
   if(_a[j]._place==i&&_a[j]._drawed==1&&_a[j]._dead==0)
    {  black(A[][3],v,i,j);//j是现在的操作数,i是所在的空格格数
         v=v+1;

    }

choice(A[][3],v);//选择出这一次的最佳移动
int i=0;
for(;i<v;i++)//执行这次的最佳移动
{
    if(A[i][0]!=-1)
    {
        if(A[i][0]==0)//吃子
        {   _a[A[i][1]]._dead=1;
            _a[A[i][2]]._x=_a[A[i][1]]._x;
            _a[A[i][2]]._y=_a[A[i][1]]._y;
            _a[A[i][2]]._place=_a[A[i][1]]._place;
             deadchess(_a[A[i][1]]._id,_a[A[i][1]]._x,_a[A[i][1]]._y);
             repaint();

        }

        if(A[v][0]==1)//逃跑
        {
            int x=0;
            int y=0;
            place_point(A[i][1],x,y);
            _a[A[i][2]]._x=x;
            _a[A[i][2]]._y=y;
            _a[A[i][2]]._place=A[i][1];
            repaint();

        }

        if(A[i][0]==2)//移动
        {
            int x=0;
            int y=0;
            place_point(A[i][1],x,y);
            _a[A[i][2]]._x=x;
            _a[A[i][2]]._y=y;
            _a[A[i][2]]._place=A[i][1];
            repaint();

        }

    }
}

if(i==v)//选择均是不移动，就顺序翻子
{
    for(int j=0;j<32;j++)
    {
        if(_a[j]._drawed==0)
          { _a[j]._drawed=1;
            repaint();
          }

    }
}

void black(int A[][3],int o,int w,int k)//w为当前棋子所在格子数，k为当前操作的棋子序号,o为当前A数组的序号
{
    int m[4][3]={-1};
     int q=w%8;
       int p=w/8;
        int t=0;

        result((p-1),q,0,k);
         result((p+1),q,1,k);
          result(p,(q+1),2,k);
           result(p,(q-1),3,k);
             choice(m[][3]);

     int i=0;
     for(;i<4;i++)
     {
         if(m[i][0]==-1)
          {
             t=t+1;
          }
         else
         {
           A[o][0]=m[i][0];
            A[o][1]=m[i][1];
              A[o][2]=m[i][2];
                A[o][3]=m[i][3];
                 break;
         }

     }
     if(i==4)
       {
         A[o][0]=-1;
          A[o][1]=-1;
            A[o][2]=-1;
              A[o][3]=-1;
       }


}

void  choice(int a[][4])
{   int flag11=0;
    int flag12=0;
    int flag13=0;
    int flag14=0;
    int i=0;
    int t=0;
    int y=0;
    int n=0;

    for(int j=0;j<4;j++)//找到是否有移动的情况
    {
        if(a[j][0]==2)
        {
            y=a[j][1];//移动到的位置
            n=j;//移动情况的序号
            break;
        }
    }

    for(;i<4;i++)
      {
        if(a[i][0]==0&&flag11==0)//存在吃子情况，清除所有不移动的选择
          { flag11=a[i][1];//所吃子的序号
              flag14=i;
            for(int j=0;j<4;j++)
               if(a[j][0]==4)
             {
                    a[j][0]=-1;
                      a[j][1]=-1;
                       a[j][2]=-1;
             }
          }

         if(a[i][0]==0&&flag11!=0)
            { flag13=a[i][1];//所吃子的序号
               if(_a[flag13].str>_a[flag11].str)
                 {

                   a[flag14][0]=-1;
                     a[flag14][1]=-1;
                      a[flag14][2]=-1;
                       flag11=a[i][1];
                         flag14=i;


                 }
               else
               {
                   a[i][0]=-1;
                     a[i][1]=-1;
                      a[i][2]=-1;
                       flag13=0;
               }
          }

        if(a[i][0]==1&&flag11!=0)//逃走还是吃子
        {
            flag12=a[i][2];//被吃子的序号
              if(_a[flag12].str>_a[flag11].str&&n!=0)
                 {
                           a[flag14][0]=-1;
                            a[flag14][1]=-1;
                              flag11=0;
                               flag14=0;
                                a[i][0]=1;
                                 a[i][1]=y;
                                  a[i][2]=a[flag14][2];
                                  a[flag14][2]=-1;
                        break;
                  }

                 }
              else
              {
                  a[i][0]=-1;
                   a[i][1]=-1;
                   a[i][2]=-1;
              }
        }


       if(a[i][0]==2)
       {
           t=t+1;
       }

}
    if(t==4)
     for(int j=1;j<4;j++)
        {
         a[j][0]=-1;
           a[j][1]=-1;
           a[j][2]=-1;
        }


 }




void result(int a,int b,int c,int d)//a代表行，b代表列，c代表数组序号，d代表当前己方的操作对象序号
   {int B=a*8+b;
     int i=0;
       if(B>=0&&B<=31)
        { for(;i<32;i++)//遍历棋子
           { //不移动                 /*黑棋*/         /*已翻面*/                                                                                   /*红棋*/              /*等于马、兵、卒的红棋*/                                                     /*未死*/
      /*       if((_a[i]._place==B&&_a[i]._color==0&&_a[i]._drawed==1)||(_a[i]._drawed==0&&_a[i]._palce==B)||(_a[i]._place==B&&_a[i]._drawed==1&&_a[i]._color==1&&_a[i].str==_a[d].str&&(_a[i]._type=="马"||_a[i]._type=="兵"||_a[i]._type=="卒"))&&_a[i]._dead==0)
             {
                 m[c][0]=4;
                   m[c][1]=0;
                     m[c][2]=d;
                       break;
             }
             //吃子
             if(_a[i]._place==B&&_a[i]._color==1&&((_a[i].str==_a[d].str&&(_a[i]._type!="马"||_a[i]._tyupe!="兵"||_a[i]._type!="卒"))||(_a[i].str<_a[d].str))&&_a[i]._drawed==1&&_a[i]._dead==0)
              {
                 m[c][0]=0;
                   m[c][1]=i;
                     m[c][2]=d;
                       break;
             }


             //逃走
             if(_a[i].drawed==1&&_a[i]._color==1&&_a[i].str>_a[d].str)
                {
                 m[c][0]=1;
                   m[c][1]=i;//吃棋者信息
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
           return;
}*/


}







