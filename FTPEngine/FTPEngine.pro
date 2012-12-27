QT       += network core-private

TARGET = FTPEngine
CONFIG(debug, debug|release): TARGET = $${TARGET}d
CONFIG += create_prl

TEMPLATE = lib

DEFINES += FTPENGINE_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ./FTPEngine/ \
    ./FTPEngine/FTPCommand/ \
    ./FTPFile/FileInfo/ \
    ./FTPFile/ \
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

SOURCES += \
    FTPEngine/ftpengine.cpp \
    FTPEngine/FTPCommand/ftpcommand.cpp \
    FTPFile/FileInfo/fileinfo.cpp \
    FTPFile/ftpfile.cpp \
    FTPEngine/FTPTransfer/ftptransfer.cpp

HEADERS += \
    ../include/ftpengine.h \
    FTPEngine/FTPCommand/ftpcommand.h \
    ../include/fileinfo.h \
    ../include/ftpfile.h \
    FTPEngine/FTPTransfer/ftptransfer.h







