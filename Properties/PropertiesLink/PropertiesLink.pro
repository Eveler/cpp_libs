#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T14:45:29
#
#-------------------------------------------------

QT       -= gui

TARGET = PropertiesLink
#CONFIG += staticlib
#CONFIG += create_prl

CONFIG(debug, debug|release): TARGET = $${TARGET}d

TEMPLATE = lib

INCLUDEPATH += ./ \
    ../../bin/ \
    ../../include/ \
    ../PropertiesView/

DEFINES += PROPERTIESLINK_LIBRARY

SOURCES += propertieslink.cpp \
    ../PropertiesView/propertiesview.cpp

HEADERS += ../../include/propertieslink.h \
    ../../include/propertiesview.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PropertiesLink.dll
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

DESTDIR = ../../bin
DLLDESTDIR = ../../bin
CONFIG(release, debug|release){
  OBJECTS_DIR = ../../temp/$$TARGET/release
  MOC_DIR = ../../temp/$$TARGET/release
  RCC_DIR = ../../temp/$$TARGET/release
  UI_DIR = ../../temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ../../temp/$$TARGET/debug
  MOC_DIR = ../../temp/$$TARGET/debug
  RCC_DIR = ../../temp/$$TARGET/debug
  UI_DIR = ../../temp/$$TARGET/debug
}

LIBS += -L..//..//bin// -lProperties






