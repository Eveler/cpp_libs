QT       += gui

TARGET = Group
CONFIG(debug, debug|release): TARGET = $${TARGET}d
CONFIG += create_prl

TEMPLATE = lib

DEFINES += GROUP_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ../Abstraction/AbstractSimpleObject/ \
    ../Abstraction/AbstractSimpleStorage/ \
    ./GroupsStorage/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Group.dll
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

DESTDIR = ../bin
DLLDESTDIR = ../bin
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

LIBS += -L../bin/ \
    -lAMSLogger \
    -lMFCCore \
    -lMFCStorage

HEADERS += \
    ../include/groupsstorage.h \
    ../include/abstractsimplestorage.h \
    ../include/abstractsimpleobject.h

SOURCES += \
    ../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    ../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    GroupsStorage/groupsstorage.cpp










