#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += network sql
TARGET = DocManager
TEMPLATE = lib
#CONFIG += staticlib release
#CONFIG += create_prl

DEFINES += DOCMANAGER_LIBRARY

#include(../mDossier/storages/ftp/ftpdocsstorage.pri)

INCLUDEPATH += ./ \
    ../include/ \
    ../include/export

SOURCES += \
    docmanager.cpp \
    docpathsdocuments.cpp \
    declardocuments.cpp \
    clientdocuments.cpp \
    docpathsdocssaver.cpp \
    docpathsdocsloader.cpp \
    abstractdocumentslist.cpp \
    abstractdoclistsaver.cpp \
    abstractdoclistloader.cpp \
    documentsmodel.cpp \
    declardocssaver.cpp \
    declardocsloader.cpp \
    clientdocssaver.cpp \
    clientdocsloader.cpp

HEADERS += \
    ../include/docmanager.h \
    ../include/docpathsdocuments.h \
    ../include/declardocuments.h \
    ../include/clientdocuments.h \
    ../include/docpathsdocssaver.h \
    ../include/docpathsdocsloader.h \
    ../include/abstractdocumentslist.h \
    ../include/abstractdoclistsaver.h \
    ../include/abstractdoclistloader.h \
    ../include/documentsmodel.h \
    ../include/declardocssaver.h \
    ../include/declardocsloader.h \
    ../include/clientdocssaver.h \
    ../include/clientdocsloader.h

RESOURCES +=

INSTALL_TO_TICKETCHOICE = E:/devel/Tests/bin
INSTALL_WIN_LIB = $$INSTALL_TO_TICKETCHOICE

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

LIBS += -lAMSLogger -lDossier
