#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T16:28:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jsonrpcTest
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3dparty/lib/ -lqjsonrpc1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3dparty/lib/ -lqjsonrpc1d
else:unix: LIBS += -L$$PWD/../../3dparty/lib/ -lqjsonrpc1

INCLUDEPATH += $$PWD/../../3dparty/qjsonrpc/src
DEPENDPATH += $$PWD/../../3dparty/qjsonrpc/src
