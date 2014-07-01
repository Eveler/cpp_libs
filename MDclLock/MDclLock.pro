#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T20:36:04
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = MDclLock
TEMPLATE = lib

exists( ../install_path.pri ){
    include(../install_path.pri)
}

DEFINES += MDCLLOCK_LIBRARY

INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

SOURCES += mdcllock.cpp \
    httpclient.cpp \
    checkconnection.cpp

HEADERS += ../include/mdcllock.h \
    httpclient.h \
    checkconnection.h

unix {
    target.path = /usr/lib
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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin_qt5/ -lAMSLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin_qt5/ -lAMSLoggerd
else:unix: LIBS += -L$$PWD/../bin_qt5/ -lAMSLogger

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3dparty/lib/ -lqjsonrpc1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3dparty/lib/ -lqjsonrpc1d
else:unix: LIBS += -L$$PWD/../3dparty/lib/ -lqjsonrpc1

INCLUDEPATH += $$PWD/../3dparty/qjsonrpc/src
DEPENDPATH += $$PWD/../3dparty/qjsonrpc/src
