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
#CONFIG += create_prl

DEFINES += AMSLOGGER_BUILD

INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

SOURCES += \
    smtp.cpp \
    amslogger.cpp

HEADERS += \
    ../include/smtp.h \
    ../include/amslogger.h

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
