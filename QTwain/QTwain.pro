#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += core gui
greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets

TARGET = QTwain
TEMPLATE = lib

exists( ../install_path.pri ){
    include(../install_path.pri)
}

DEFINES += QTWAIN_LIBRARY
DEFINES += NOMINMAX
#DEFINES += SCAN_DEBUG

INCLUDEPATH += ./ \
    ../include/

SOURCES += \
    twain/twaincpp.cpp \
    twain/qtwaininterface.cpp \
    twain/qtwain.cpp \
    twain/dib.cpp \
    twain/dibutil.c \
    twain/dibfile.c \
    mtwain.cpp

HEADERS += \
    ../include/twaincpp.h \
    ../include/twain.h \
    twain/stdafx.h \
    ../include/qtwaininterface.h \
    ../include/qtwain.h \
    twain/dibutil.h \
    twain/dibapi.h \
    ../include/dib.h \
    mtwain.h

RESOURCES +=

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
