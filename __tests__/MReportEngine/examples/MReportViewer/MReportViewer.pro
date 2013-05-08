#-------------------------------------------------
#
# Project created by QtCreator 2013-04-12T09:44:36
#
#-------------------------------------------------

QT       += core gui network webkit xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = MReportViewer
TEMPLATE = app


INCLUDEPATH += ./ \
    ./bin/ \
    ../../include/ \
    ../../../../include/ \
    ./MDateDialog/


symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MReportEngine.dll
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

DESTDIR = ./bin
DLLDESTDIR = ./bin

LIB_LIST = \
    -lAMSLogger \
    -lMReportEngine \
    -lMWidgets

LIBS += -L./bin/ \
    $${LIB_LIST}

CONFIG(release, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/release
  MOC_DIR = ./temp/$$TARGET/release
  RCC_DIR = ./temp/$$TARGET/release
  UI_DIR = ./temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/debug
  MOC_DIR = ./temp/$$TARGET/debug
  RCC_DIR = ./temp/$$TARGET/debug
  UI_DIR = ./temp/$$TARGET/debug
}

SOURCES += main.cpp\
        mainwindow.cpp \
    mreportviewer.cpp \
    mreportviewer_p.cpp \
    MDateDialog/mdatedialog.cpp

HEADERS  += mainwindow.h \
    ../../include/mreportviewer.h \
    mreportviewer_p.h \
    MDateDialog/mdatedialog.h

FORMS    += mainwindow.ui \
    mreportviewer.ui \
    MDateDialog/mdatedialog.ui

RESOURCES += \
    MDateDialog/MDateDialog_Icons.qrc
