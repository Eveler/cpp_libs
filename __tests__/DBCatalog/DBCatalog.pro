#-------------------------------------------------
#
# Project created by QtCreator 2013-04-02T15:52:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBCatalog
TEMPLATE = app


include(./dbcatalog_config.pri)


LIB_LIST = \
    -lAMSLogger \
    -lMFCCore

INCLUDEPATH += \
    $${DBC_INTERFACES} \
    $${DBC_DEST_DIR}

message( $${DBC_INTERFACES} )

DESTDIR = $${DBC_DEST_DIR}
DLLDESTDIR = $${DBC_DEST_DIR}

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

SOURCES += main.cpp\
    dbcatalog.cpp

HEADERS  += dbcatalog.h

FORMS    += dbcatalog.ui

RC_FILE = myapp.rc
