#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT       -= gui
QT     += network
TARGET = AMSLogger
TEMPLATE = lib
#CONFIG += staticlib release
CONFIG += create_prl

SOURCES += amslogger.cpp \
    smtp.cpp

HEADERS += amslogger.h \
    smtp.h
#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/local/lib
#    }
#    INSTALLS += target
#}
DESTDIR = ../../lib
OBJECTS_DIR = ../../temp/AMSLogger
MOC_DIR = ../../temp/AMSLogger
