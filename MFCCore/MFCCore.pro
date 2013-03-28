#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T14:45:29
#
#-------------------------------------------------

QT       += gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MFCCore
CONFIG(debug, debug|release): TARGET = $${TARGET}d
#CONFIG += create_prl

TEMPLATE = lib

DEFINES += EXPORT_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ./Abstraction/AbstractSimpleObject/ \
    ./Abstraction/AbstractSimpleStorage/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MFCCore.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

greaterThan(QT_MAJOR_VERSION, 4) {
  DESTDIR = ../bin_qt5
  DLLDESTDIR = ../bin_qt5

  LIBS += -L../bin_qt5/ \
      -lmuCalculator
}

lessThan(QT_MAJOR_VERSION, 5) {
  DESTDIR = ../bin
  DLLDESTDIR = ../bin

  LIBS += -L../bin/ \
      -lmuCalculator \
      -lAMSLogger
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

HEADERS += \
    ../include/mfccore.h \
    ../include/abstractsimpleobject.h \
    ../include/abstractsimplestorage.h

SOURCES += \
    mfccore.cpp \
    Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp

#greaterThan( QT_MAJOR_VERSION, 4 ) {
#  LIBS += -L../bin_qt5/ \
#      -lAMSLogger
#}

