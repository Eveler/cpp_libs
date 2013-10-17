#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T11:36:56
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StorageTest
TEMPLATE = app

exists( ../../install_path.pri ){
    include(../../install_path.pri)
}


INCLUDEPATH += ./ \
    ../../include/ \
    ./ReceptionDocmanager/ \
    ./ReceptionDocmanager/AddDocWizard/ \
    ../../../ElectroDocViewer/EDVProcess/

SOURCES += main.cpp\
        mainwindow.cpp \
    ReceptionDocmanager/AddDocWizard/wizard_adddoc.cpp \
    ReceptionDocmanager/AddDocWizard/docsourcepage.cpp \
    ReceptionDocmanager/AddDocWizard/createdocspage.cpp \
    ReceptionDocmanager/AddDocWizard/clientdocspage.cpp \
    ReceptionDocmanager/AddDocWizard/declardocspage.cpp \
    ReceptionDocmanager/AddDocWizard/summarypage.cpp \
    ReceptionDocmanager/receptiondocmanager_p.cpp \
    ReceptionDocmanager/widget_receptiondocmanager.cpp \
    ReceptionDocmanager/AddDocWizard/dialog_docdetails.cpp \
    ReceptionDocmanager/requireddocs.cpp \
    ReceptionDocmanager/reqdocsmodel.cpp \
    clientinfoloader.cpp \
    docpathsinfoloader.cpp \
    ReceptionDocmanager/booldelegate.cpp \
    ReceptionDocmanager/dialog_clientdocscreate.cpp \
    ReceptionDocmanager/dialog_selectdocument.cpp \
    ReceptionDocmanager/toolbuttondelegate.cpp \
    declarinfoloader.cpp

HEADERS  += mainwindow.h \
    ReceptionDocmanager/AddDocWizard/wizard_adddoc.h \
    ReceptionDocmanager/AddDocWizard/docsourcepage.h \
    ReceptionDocmanager/AddDocWizard/createdocspage.h \
    ReceptionDocmanager/AddDocWizard/clientdocspage.h \
    ReceptionDocmanager/AddDocWizard/declardocspage.h \
    ReceptionDocmanager/AddDocWizard/summarypage.h \
    ReceptionDocmanager/widget_receptiondocmanager.h \
    ReceptionDocmanager/receptiondocmanager_p.h \
    ReceptionDocmanager/AddDocWizard/dialog_docdetails.h \
    ReceptionDocmanager/requireddocs.h \
    ReceptionDocmanager/reqdocsmodel.h \
    clientinfoloader.h \
    docpathsinfoloader.h \
    ReceptionDocmanager/booldelegate.h \
    ReceptionDocmanager/dialog_clientdocscreate.h \
    ReceptionDocmanager/dialog_selectdocument.h \
    ReceptionDocmanager/toolbuttondelegate.h \
    declarinfoloader.h

FORMS    += mainwindow.ui \
    ReceptionDocmanager/AddDocWizard/docsourcepage.ui \
    ReceptionDocmanager/AddDocWizard/createdocspage.ui \
    ReceptionDocmanager/AddDocWizard/clientdocspage.ui \
    ReceptionDocmanager/AddDocWizard/declardocspage.ui \
    ReceptionDocmanager/AddDocWizard/summarypage.ui \
    ReceptionDocmanager/widget_receptiondocmanager.ui \
    ReceptionDocmanager/AddDocWizard/dialog_docdetails.ui \
    ReceptionDocmanager/dialog_clientdocscreate.ui \
    ReceptionDocmanager/dialog_selectdocument.ui

DESTDIR = ./bin
DLLDESTDIR = ./bin
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

LIBS += -L./bin \
  -lAMSLogger \
  -lDocManager \
  -lDossier \
  -lEDVProcess \
  -lMFCCore

RESOURCES += \
    ReceptionDocmanager/ReceprionDocmanager_Icons.qrc
