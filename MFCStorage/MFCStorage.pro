#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T14:45:29
#
#-------------------------------------------------

QT       += gui sql network

TARGET = MFCStorage
CONFIG(debug, debug|release): TARGET = $${TARGET}d
CONFIG += create_prl

TEMPLATE = lib

DEFINES += MFCSTORAGE_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ../Properties/Properties/ \
    ../Properties/PropertiesLink/ \
    ../Properties/PropertiesView/ \
    ../StorageItemModel/ \
    ../StorageItemModel/MFCProperty/ \
    ../StorageItemModel/MFCRecord/ \
    ../PropertiesSqlWorker/ \
    ../pgdb/ \
    ../StorageEditor/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MFCStorage.dll
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

HEADERS += \
    ../include/storageitemmodel.h \
    ../include/storageeditor.h \
    ../include/propertiesview.h \
    ../include/propertiessqlworker.h \
    ../include/propertieslink.h \
    ../include/properties.h \
    ../include/pgdb.h \
    ../include/mfcrecord.h \
    ../include/mfcproperty.h

SOURCES += \
    ../pgdb/pgdb.cpp \
    ../Properties/Properties/properties.cpp \
    ../Properties/PropertiesLink/propertieslink.cpp \
    ../Properties/PropertiesView/propertiesview.cpp \
    ../StorageItemModel/MFCProperty/mfcproperty.cpp \
    ../StorageItemModel/MFCRecord/mfcrecord.cpp \
    ../StorageItemModel/storageitemmodel.cpp \
    ../StorageEditor/storageeditor.cpp \
    ../PropertiesSqlWorker/propertiessqlworker.cpp
