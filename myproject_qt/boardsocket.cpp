#include "boardsocket.h"
#include<QDebug>
#include<QTcpSocket>
boardsocket::boardsocket()
{
       _socket=new QTcpSocket(this);//客户端
       _socket->connectToHost(QHostAddress("127.0.0.1"),9999);
       //connect()
}

boardsocket::~boardsocket()
{

}
void boardsocket::soltRecv()
{
   QByteArray ba= _socket->readAll();//接收

   for(int i=0;i<32;i++)
     {
         _a[i]._x=ba[i*7];
         _a[i]._y=ba[i*7+1];
         _a[i]._place= ba[i*7+2];
         _a[i]._drawed=ba[i*7+3];
         _a[i]._dead=ba[i*7+4];
     }

   char a1[160];
   for(int i=0;i<32;i++)
     {
         a1[i*7]=_a[i]._x;
         a1[i*7+1]=_a[i]._y;
         a1[i*7+2]=_a[i]._place;
         a1[i*7+3]=_a[i]._drawed;
         a1[i*7+4]=_a[i]._dead;
     }
   _socket->write(a1,160);

}

