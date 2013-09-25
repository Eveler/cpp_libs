#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T11:36:12
#
#-------------------------------------------------

QT       += core gui sql printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Doclist_v2_test
TEMPLATE = app

INCLUDEPATH += ../../include/ \
    ../../../MFCCtrlDate/dossier/

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../MFCCtrlDate/dossier/doclist_v2.cpp

HEADERS  += mainwindow.h \
    ../../../MFCCtrlDate/dossier/doclist_v2.h

FORMS    += mainwindow.ui \
    ../../../MFCCtrlDate/dossier/doclist_v2.ui

LIBS += -lDocManager -lAMSLogger -lDossier -lDocWidgets

RESOURCES += \
    ../../../MFCCtrlDate/icons.qrc
