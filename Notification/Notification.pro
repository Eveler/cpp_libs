QT       += gui

TARGET = Notification
CONFIG(debug, debug|release): TARGET = $${TARGET}d
#CONFIG += create_prl

TEMPLATE = lib

DEFINES += NOTIFICATION_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ./Notification/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Notification.dll
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

LIBS += -L../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore \
    -lUser

HEADERS += \
    ../include/notification.h \
    ../include/notificationsstorage.h

SOURCES += \
    Notification/notification.cpp \
    NotificationsStorage/notificationsstorage.cpp








