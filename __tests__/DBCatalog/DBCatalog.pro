#-------------------------------------------------
#
# Project created by QtCreator 2013-04-02T15:52:43
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBCatalog
TEMPLATE = app


include(./dbcatalog_config.pri)


LIB_LIST = \
    -lAMSLogger \
    -lMFCCore \
    -lMFCWidgets

INCLUDEPATH += \
    $${DBC_INTERFACES} \
    $${DBC_DEST_DIR} \
    $${DBC_LIBS_INCLUDE} \
    ./Configuration/ \
    ./Configuration/PluginsSourceLoader/

DESTDIR = $${DBC_DEST_DIR}
DLLDESTDIR = $${DBC_DEST_DIR}

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

LIBS += -L$${DBC_LIBS_BIN} \
    $$LIB_LIST

SOURCES += main.cpp\
    dbcatalog.cpp \
    dbcatalog_p.cpp \
    Configuration/widget_configuration.cpp \
    Configuration/configuration_p.cpp \
    Configuration/PluginsSourceLoader/widget_pluginssourceloader.cpp \
    Configuration/PluginsSourceLoader/pluginssourceloader_p.cpp

HEADERS  += dbcatalog.h \
    dbcatalog_p.h \
    Configuration/widget_configuration.h \
    Configuration/configuration_p.h \
    Configuration/PluginsSourceLoader/widget_pluginssourceloader.h \
    Configuration/PluginsSourceLoader/pluginssourceloader_p.h

FORMS    += dbcatalog.ui \
    Configuration/widget_configuration.ui \
    Configuration/PluginsSourceLoader/widget_pluginssourceloader.ui

RC_FILE = myapp.rc

RESOURCES += \
    Configuration/Configuration_icons.qrc \
    Configuration/PluginsSourceLoader/PluginsSourceLoader_icons.qrc
