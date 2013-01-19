QT       += network core

TARGET = FTPEngine
CONFIG(debug, debug|release): TARGET = $${TARGET}d
CONFIG += create_prl

TEMPLATE = lib

DEFINES += FTPENGINE_LIBRARY

INCLUDEPATH += ./ \
    ../bin_qt5/ \
    ../include/ \
    ./FTPEngine/ \
    ./FTPEngine/FTPCommand/ \
    ./FTPEngine/FTPCommandsPool/ \
    ./FTPFile/FileInfo/ \
    ./FTPEngine/FTPTransfer/

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
}
lessThan( QT_MAJOR_VERSION, 5 ) {
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

SOURCES += \
    FTPEngine/ftpengine.cpp \
    FTPEngine/FTPCommand/ftpcommand.cpp \
    FTPEngine/FTPCommandsPool/ftpcommandspool.cpp \
    FTPFile/FileInfo/fileinfo.cpp \
    FTPEngine/FTPTransfer/ftptransfer.cpp

HEADERS += \
    ../include/ftpengine_export.h \
    ../include/ftpengine.h \
    FTPEngine/FTPCommand/ftpcommand.h \
    FTPEngine/FTPCommandsPool/ftpcommandspool.h \
    ../include/fileinfo.h \
    FTPEngine/FTPTransfer/ftptransfer.h

greaterThan( QT_MAJOR_VERSION, 4 ) {
  LIBS += -L../bin_qt5/ \
      -lAMSLogger
}





