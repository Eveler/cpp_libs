#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += network
TARGET = mDossier
TEMPLATE = lib
#CONFIG += staticlib release
#CONFIG += create_prl

DEFINES += DOSSIER_LIBRARY

INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

SOURCES += \
    document/mfcdocument.cpp \
    document/docattachment.cpp \
    document/docattachments.cpp \
    document/mfcdocumentpages.cpp \
    document/mfcdocumentpage.cpp \
    widgets/electrodoc_v2.cpp

HEADERS += \
    ../include/mfcdocument.h \
    ../include/mfcdocumentpages.h \
    ../include/mfcdocumentpage.h \
    ../include/docattachments.h \
    ../include/docattachment.h \
    ../include/electrodoc_v2.h

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

LIBS += -lAMSLogger

FORMS += \
    widgets/electrodoc_v2.ui

RESOURCES += \
    acceptapplications__icons.qrc \
    widgets/electrodoc_icons.qrc
