#ifndef BOARDSERVER_H
#define BOARDSERVER_H
#include "board1.h"
#include<QTcpServer>
#include<QTcpSocket>
class boardserver :public board1
{
    Q_OBJECT
public:
    boardserver(bool server);
    ~boardserver();

    QTcpServer*_server;
    QTcpSocket*_socket;
public slots:
    void slotnewconnection();
    void serverslot();

};

#endif // BOARDSERVER_H
