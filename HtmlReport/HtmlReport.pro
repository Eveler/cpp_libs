#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T19:27:11
#
#-------------------------------------------------

QT       += gui network

TARGET = HtmlReport
TEMPLATE = lib

exists( ../install_path.pri ){
    include(../install_path.pri)
}

DEFINES += HTMLREPORT_LIBRARY

SOURCES += htmlreport.cpp

HEADERS += ../include/htmlreport.h

INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

unix:!symbian {

    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32 {
    target.path = $$INSTALL_WIN_LIB
    INSTALLS += target
}

greaterThan(QT_MAJOR_VERSION, 4) {
  DESTDIR = ../bin_qt5
  DLLDESTDIR = ../bin_qt5
}
lessThan(QT_MAJOR_VERSION, 5) {
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

greaterThan(QT_MAJOR_VERSION, 4) {
  LIBS += -L../bin_qt5
}
lessThan(QT_MAJOR_VERSION, 5) {
  LIBS += -L../bin
}

LIBS += -lAMSLogger -lMFCCore
