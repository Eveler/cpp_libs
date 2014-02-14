#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T12:11:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TwainTest
TEMPLATE = app

INCLUDEPATH += ./ \
    ../../include/ \

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lAMSLogger
win32 {
LIBS += -lQTwain
}
