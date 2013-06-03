QT       += gui core network

greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets

TARGET = MFCWidgets
CONFIG(debug, debug|release): TARGET = $${TARGET}d
#CONFIG += create_prl

TEMPLATE = lib

DEFINES += EXPORT_LIB_MWIDGETS

LIB_LIST =

INCLUDEPATH += ./ \
    ../bin/ \
    ../bin_qt5/ \
    ../include/ \
    ./MainWindow/ \
    ./Widget/


symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = FTPEngine.dll
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

greaterThan( QT_MAJOR_VERSION, 4 ) {
  DESTDIR = ../bin_qt5
  DLLDESTDIR = ../bin_qt5

  LIBS += -L../bin_qt5/ \
      $$LIB_LIST
}
lessThan( QT_MAJOR_VERSION, 5 ) {
  DESTDIR = ../bin
  DLLDESTDIR = ../bin

  LIBS += -L../bin/ \
      $$LIB_LIST
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

HEADERS += \
    ../include/mfcwidgets.h \


include(./MWidgetsCore/MWidgetsCore.pri)
include(./Widget_Treelist/Widget_Treelist.pri)
include(./Menu_PeriodDates/Menu_PeriodDates.pri)
