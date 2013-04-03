#-------------------------------------------------
#
# Project created by QtCreator 2013-01-18T11:04:56
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBMemberCatalog
TEMPLATE = lib


#-------------------------------------------------
include(../../DBCatalog/dbcatalog_config.pri)

#-------------------------------------------------
LIB_LIST = \
    -lAMSLogger \
    -lMFCCore

INCLUDEPATH += \
    ../$${DBC_LIBS_INCLUDE} \
    ../$${DBC_DEST_DIR} \
    ../

DESTDIR = ../$${DBC_PLUGINS_DIR}
DLLDESTDIR = ../$${DBC_PLUGINS_DIR}

LIBS += -L../$${DBC_LIBS_BIN} \
    $$LIB_LIST

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


#-------------------------------------------------
SOURCES += \
    dbmembercatalog.cpp

HEADERS += \
    ../$${DBC_INTERFACES}dbcatalog_interface.h \
    dbmembercatalog.h

FORMS   +=

