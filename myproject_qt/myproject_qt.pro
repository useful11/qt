#-------------------------------------------------
#
# Project created by QtCreator 2020-09-14T21:49:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myproject_qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    board.cpp \
    chess.cpp \
    board1.cpp \
    board2.cpp \
    rules.cpp \
    boardserver.cpp \
    boardsocket.cpp

HEADERS += \
        widget.h \
    board.h \
    chess.h \
    board1.h \
    board2.h \
    rules.h \
    boardserver.h \
    boardsocket.h

FORMS += \
        widget.ui \
    board.ui \
    board1.ui \
    board2.ui \
    rules.ui
CONFIG +==C++11

DISTFILES +=
