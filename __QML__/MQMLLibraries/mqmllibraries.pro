TEMPLATE = lib
TARGET = MQMLLibraries
QT += qml quick
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = Extensions.MQMLLibraries

# Input
SOURCES += \
    mqmllibraries_plugin.cpp \
    logreader.cpp \
    Tree/treeitem.cpp \
    Tree/treemodel.cpp

HEADERS += \
    mqmllibraries_plugin.h \
    logreader.h \
    Tree/treeitem.h \
    Tree/treemodel.h

OTHER_FILES = qmldir

QT_INSTALL_QML = C:/Qt/Qt5.1.1/5.1.1/mingw48_32/qml

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
