#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T12:16:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WiaTest
TEMPLATE = app

INCLUDEPATH += ./ \
    ../../include/

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lQWia -lAMSLogger
