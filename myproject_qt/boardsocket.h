#ifndef BOARDSOCKET_H
#define BOARDSOCKET_H
#include "board1.h"
#include<QTcpServer>
#include<QTcpSocket>
#include"boardserver.h"
class boardsocket :public board1
{
    Q_OBJECT
public:
    boardsocket();
    ~boardsocket();
    QTcpSocket*_socket;
public slots:
    void soltRecv();
};

#endif // BOARDSERVER_H
