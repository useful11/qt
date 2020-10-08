#include "widget.h"
#include <QApplication>
#include "board.h"
#include "board1.h"
#include "chess.h"
#include "board2.h"
#include"rules.h"
#include <QDebug>
#include "boardserver.h"
#include"boardsocket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();

  /* /* boardserver w;
    w.show();

    boardsocket w1;
    w1.show();*/
    return a.exec();
}
