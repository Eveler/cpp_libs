#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += network

TARGET = Dossier
TEMPLATE = lib
#CONFIG += staticlib release
#CONFIG += create_prl

DEFINES += DOSSIER_LIBRARY


exists( ../install_path.pri ){
    include(../install_path.pri)
}
include(storages/ftp/ftpdocsstorage.pri)

INCLUDEPATH += ./ \
    ../include/

SOURCES += \
    document/mfcdocument.cpp \
    document/docattachment.cpp \
    document/docattachments.cpp \
    document/mfcdocumentpages.cpp \
    document/mfcdocumentpage.cpp \
    storages/ftp/ftpdocsstorage.cpp \
    storages/abstractdocsstorage.cpp \
    providers/mfcdocumentioprovider.cpp \
    providers/mfcdocumentzipper.cpp \
    document/mfcdocumentinfo.cpp

HEADERS += \
    ../include/mfcdocument.h \
    ../include/mfcdocumentpages.h \
    ../include/mfcdocumentpage.h \
    ../include/docattachments.h \
    ../include/docattachment.h \
    ../include/ftpdocsstorage.h \
    ../include/abstractdocsstorage.h \
    ../include/mfcdocumentioprovider.h \
    ../include/mfcdocumentzipper.h \
    ../include/mfcdocumentinfo.h \
    ../include/export/dossier_export.h

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

CONFIG(release, debug|release) LIBS += -lAMSLogger -lFTPEngine -lquazip
CONFIG(debug, debug|release) LIBS += -lAMSLogger -lFTPEngined -lquazip
