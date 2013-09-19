#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += core gui
greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets

TARGET = QTwain
TEMPLATE = lib

DEFINES += QTWAIN_LIBRARY


INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

SOURCES += \
    twain/twaincpp.cpp \
    twain/qtwaininterface.cpp \
    twain/qtwain.cpp \
    twain/dib.cpp \
    twain/dibutil.c \
    twain/dibfile.c

HEADERS += \
    twain/twaincpp.h \
    twain/twain.h \
    twain/stdafx.h \
    ../include/qtwaininterface.h \
    ../include/qtwain.h \
    twain/dibutil.h \
    twain/dibapi.h \
    twain/dib.h

RESOURCES +=

INSTALL_TO = E:/devel/MFCScanProject/bin
QT_INSTALL_WIN_LIB = $$INSTALL_TO

unix:!symbian {

    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32 {
    target.path = $$QT_INSTALL_WIN_LIB
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

lessThan(QT_MAJOR_VERSION,5){
win32:LIBS += -L"./twain" \
    -lGdi32
}
