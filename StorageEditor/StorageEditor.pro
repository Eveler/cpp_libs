#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T14:45:29
#
#-------------------------------------------------

QT       += gui sql network

TARGET = StorageEditor
CONFIG(debug, debug|release): TARGET = $${TARGET}d
#CONFIG += create_prl

TEMPLATE = lib

DEFINES += STORAGEEDITOR_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ../pgdb/

SOURCES += storageeditor.cpp \
    ../pgdb/pgdb.cpp

HEADERS += ../include/storageeditor.h \
    ../include/pgdb.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = StorageEditor.dll
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

LIBS += -L..//bin// \
    -lProperties \
    -lPropertiesLink \
    -lPropertiesView \
    -lStorageItemModel \
    -lPropertiesSqlWorker

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




