#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT       -= gui
QT     += network
TARGET = AMSLogger
TEMPLATE = lib
#CONFIG += staticlib release
CONFIG += create_prl

DEFINES += AMSLOGGER_BUILD

INCLUDEPATH += ./ \
    ../include/

SOURCES += amslogger.cpp \
    smtp.cpp

HEADERS += ../include/amslogger.h \
    ../include/smtp.h

DESTDIR = ../bin
DLLDESTDIR = ../bin
CONFIG(release, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/release
  MOC_DIR = ../temp/$$TARGET/release
  RCC_DIR = ../temp/$$TARGET/release
  UI_DIR = ../temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/debug
  MOC_DIR = ../temp/$$TARGET/debug
  RCC_DIR = ../temp/$$TARGET/debug
  UI_DIR = ../temp/$$TARGET/debug
}
