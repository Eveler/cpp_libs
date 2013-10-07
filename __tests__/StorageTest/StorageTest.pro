#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T11:36:56
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StorageTest
TEMPLATE = app

exists( ../../install_path.pri ){
    include(../../install_path.pri)
}


INCLUDEPATH += ./ \
    ../../include/

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DESTDIR = ./bin
DLLDESTDIR = ./bin
CONFIG(release, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/release
  MOC_DIR = ./temp/$$TARGET/release
  RCC_DIR = ./temp/$$TARGET/release
  UI_DIR = ./temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/debug
  MOC_DIR = ./temp/$$TARGET/debug
  RCC_DIR = ./temp/$$TARGET/debug
  UI_DIR = ./temp/$$TARGET/debug
}

LIBS += -L./bin \
  -lAMSLogger \
  -lDocManager \
  -lDossier
