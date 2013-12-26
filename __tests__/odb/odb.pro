#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T00:15:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = odb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    declar.cpp

HEADERS  += mainwindow.h \
    declar.h

FORMS    += mainwindow.ui

ODB_FILES += declar.h
ODB_FLAGS = --database pgsql --profile qt --generate-schema --generate-query --generate-session
include(../../3dparty/odb/odb.pri)
LIBS += -lodb-pgsql
