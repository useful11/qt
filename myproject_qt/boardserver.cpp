#include "boardserver.h"
#include<QDebug>
#include"boardsocket.h"
boardserver::boardserver(bool server)
{
   _server=NULL;
   _socket=NULL;
   if(server==true)
   {
       _server=new QTcpServer(this);//服务器端
       _server->listen(QHostAddress::Any,9999);

       connect(_server,SIGNAL(newConnection()),
               this,SLOT(slotnewconnection()));
       //connect()

}
}

boardserver::~boardserver()
{

}


void boardserver::slotnewconnection()
{   qDebug()<<"111111"; //链接成功
    if(_socket) return;

    _socket=_server->nextPendingConnection();//服务器的通信套接字
    connect(_socket,SIGNAL(readyRead()),this,SLOT(serverslot()));

}


void boardserver::serverslot(){
   char a[160];
    for(int i=0;i<32;i++)
      {
          a[i*7]=_a[i]._x;
          a[i*7+1]=_a[i]._y;
          a[i*7+2]=_a[i]._place;
          a[i*7+3]=_a[i]._drawed;
          a[i*7+4]=_a[i]._dead;
      }
    _socket->write(a,160);

}
