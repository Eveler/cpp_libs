#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT     += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DocmanagerWidgets
TEMPLATE = lib

DEFINES += DOCMANAGERWIDGETS_LIBRARY


exists( ../../Libs/install_path.pri ){
    include(../../Libs/install_path.pri)
}

INCLUDEPATH += ./ \
    ../include/ \
    Dialogs/ \
    ../../ElectroDocViewer/EDVProcess/

SOURCES += \
    Dialogs/dialog_selectdocument.cpp \
    Dialogs/dialog_docdetails.cpp \
    Dialogs/dialog_clientdocscreate.cpp

HEADERS += \
    ../include/export/docmanagerwidgets_export_lib.h \
    ../include/dialog_selectdocument.h \
    ../include/dialog_docdetails.h \
    ../include/dialog_clientdocscreate.h

FORMS += \
    Dialogs/dialog_selectdocument.ui \
    Dialogs/dialog_docdetails.ui \
    Dialogs/dialog_clientdocscreate.ui

RESOURCES += \
    DocmanagerWidgets_Icons.qrc

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
  LIBS += -L../bin_qt5
}
lessThan(QT_MAJOR_VERSION, 5) {
  DESTDIR = ../bin
  DLLDESTDIR = ../bin
  LIBS += -L../bin
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

LIBS += -L../bin_qt5 \
  -lAMSLogger \
  -lDocManager \
  -lDossier \
  -lDocWidgets \
  -lMFCCore \
  -lFTPEngine

LIBS += -L../../ElectroDocViewer/bin \
  -lEDVProcess

