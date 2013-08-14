#-------------------------------------------------
#
# Project created by QtCreator 2013-07-20T19:47:42
#
#-------------------------------------------------

QT       += qml quick sql

qtHaveModule(widgets) {
    QT += widgets
}

TARGET = DateTimeEditApp

TEMPLATE = app

INCLUDEPATH *= . \
    ./bin/ \
    src/

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

DESTDIR = ./bin
DLLDESTDIR = ./bin

LIB_LIST =

LIBS += -L./bin/ \
    $${LIB_LIST}

SOURCES += main.cpp

RESOURCES += \
    content.qrc

OTHER_FILES += \
    content/DateTimeEditApp.qml \
    content/DateTimeEdit.qml

