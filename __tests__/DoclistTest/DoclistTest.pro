#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T20:13:11
#
#-------------------------------------------------

QT       += core gui printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoclistTest
TEMPLATE = app

exists( ../../install_path.pri ){
    include(../../install_path.pri)
}


SOURCES += main.cpp\
        mainwindow.cpp \
    Doclists/doclists.cpp

HEADERS  += mainwindow.h \
    Doclists/doclists.h

FORMS    += mainwindow.ui

DESTDIR = ./bin

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

LIBS += -L$${DESTDIR} \
  -lDossier \
  -lDocManager \
  -lDocWidgets \
  -lAMSLogger
