TEMPLATE = lib
TARGET = MAKCDataset
QT += qml quick sql
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = extensions.mihail.makcdataset

LIB_LIST = \
    -lMModels \
    -lMDataset

INCLUDEPATH += ./ \
    ../../include/ \
    ./Doctype/ \
    ./Document/ \
    ./Human/ \
    ./Organization/


# Input
SOURCES += \
    makcdataset_plugin.cpp \
    Human/mhumandatasource.cpp \
    Human/mhumandbwrapper.cpp \
    Document/mdocumentdatasource.cpp \
    Document/mdocumentdbwrapper.cpp \
    makcdataset.cpp \
    Doctype/mdoctypedbwrapper.cpp \
    Doctype/mdoctypedatasource.cpp \
    Organization/morganizationdbwrapper.cpp \
    Organization/morganizationdatasource.cpp

HEADERS += \
    makcdataset_plugin.h \
    Human/mhumandatasource.h \
    Human/mhumandbwrapper.h \
    Document/mdocumentdatasource.h \
    Document/mdocumentdbwrapper.h \
    makcdataset.h \
    Doctype/mdoctypedbwrapper.h \
    Doctype/mdoctypedatasource.h \
    Organization/morganizationdbwrapper.h \
    Organization/morganizationdatasource.h

OTHER_FILES = qmldir

QT_5_1_1_MINGW = C:/Qt/Qt5.1.1/5.1.1/mingw48_32/qml
QT_5_2_0_MINGW = C:/Qt/Qt5.2.0/5.2.0/mingw48_32/qml
QT_INSTALL_QML = $$QT_5_2_0_MINGW

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

win32 {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

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

LIBS += -L../../bin_qt5/ \
    $$LIB_LIST

