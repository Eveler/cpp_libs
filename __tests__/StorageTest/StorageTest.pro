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
    ./ReceprionDocmanager/ \
    ./ReceprionDocmanager/AddDocWizard/ \
    ../../../ElectroDocViewer/EDVProcess/

SOURCES += main.cpp\
        mainwindow.cpp \
    ReceprionDocmanager/AddDocWizard/wizard_adddoc.cpp \
    ReceprionDocmanager/AddDocWizard/docsourcepage.cpp \
    ReceprionDocmanager/AddDocWizard/createdocspage.cpp \
    ReceprionDocmanager/AddDocWizard/clientdocspage.cpp \
    ReceprionDocmanager/AddDocWizard/declardocspage.cpp \
    ReceprionDocmanager/AddDocWizard/summarypage.cpp \
    ReceprionDocmanager/receptiondocmanager_p.cpp \
    ReceprionDocmanager/widget_receptiondocmanager.cpp \
    ReceprionDocmanager/AddDocWizard/dialog_docdetails.cpp \
    clientinfoloader.cpp

HEADERS  += mainwindow.h \
    ReceprionDocmanager/AddDocWizard/wizard_adddoc.h \
    ReceprionDocmanager/AddDocWizard/docsourcepage.h \
    ReceprionDocmanager/AddDocWizard/createdocspage.h \
    ReceprionDocmanager/AddDocWizard/clientdocspage.h \
    ReceprionDocmanager/AddDocWizard/declardocspage.h \
    ReceprionDocmanager/AddDocWizard/summarypage.h \
    ReceprionDocmanager/widget_receptiondocmanager.h \
    ReceprionDocmanager/receptiondocmanager_p.h \
    ReceprionDocmanager/AddDocWizard/dialog_docdetails.h \
    clientinfoloader.h

FORMS    += mainwindow.ui \
    ReceprionDocmanager/AddDocWizard/docsourcepage.ui \
    ReceprionDocmanager/AddDocWizard/createdocspage.ui \
    ReceprionDocmanager/AddDocWizard/clientdocspage.ui \
    ReceprionDocmanager/AddDocWizard/declardocspage.ui \
    ReceprionDocmanager/AddDocWizard/summarypage.ui \
    ReceprionDocmanager/widget_receptiondocmanager.ui \
    ReceprionDocmanager/AddDocWizard/dialog_docdetails.ui

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
  -lEDVProcess
