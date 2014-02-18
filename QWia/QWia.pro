#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T20:02:46
#
#-------------------------------------------------

QT       -= gui
QT += axcontainer

TARGET = QWia
TEMPLATE = lib

#TYPELIBS = $$system(dumpcpp -getfile {94A0E92D-43C0-494E-AC29-FD45948A5221})

exists( ../install_path.pri ){
    include(../install_path.pri)
}

DEFINES += QWIA_LIBRARY

INCLUDEPATH += ./ \
    ../include/

SOURCES += qwia.cpp

HEADERS += \
    ../include/export/qwia_export.h \
    ../include/qwia.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

greaterThan(QT_MAJOR_VERSION, 4) {
  LIBS += -L../bin_qt5
  DESTDIR = ../bin_qt5
  DLLDESTDIR = ../bin_qt5
}
lessThan(QT_MAJOR_VERSION, 5) {
  LIBS += -L../bin
  DESTDIR = ../bin
  DLLDESTDIR = ../bin
}
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

#LIBS += -LC:\Windows\System32 -lwiaaut -LC:\Windows\SysWOW64 -lcrtdll
LIBS += -lAMSLogger
