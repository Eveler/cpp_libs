#-------------------------------------------------
#
# Project created by QtCreator 2013-09-17T11:46:29
#
#-------------------------------------------------

QT       += widgets network core

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = DocWidgets
TEMPLATE = lib

DEFINES += DOCWIDGETS_LIBRARY

INCLUDEPATH += ./ \
    ../include/ \

SOURCES += \
    widgets/mfcwidget.cpp \
    widgets/electrodoc_v2.cpp \
    widgets/documentmetadata.cpp \
    widgets/docpagewidget.cpp \
    widgets/docpagesviewer.cpp

HEADERS +=\
    ../include/mfcwidget.h \
    ../include/electrodoc_v2.h \
    ../include/documentmetadata.h \
    ../include/docpagewidget.h \
    ../include/docpagesviewer.h \
    ../include/export/docwidgets_export.h

FORMS += \
    widgets/electrodoc_v2.ui \
    widgets/documentmetadata.ui

RESOURCES += \
    widgets/electrodoc_icons.qrc

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

LIBS += -lDossier -lQTwain
