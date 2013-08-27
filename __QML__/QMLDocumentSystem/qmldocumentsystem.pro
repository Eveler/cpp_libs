TEMPLATE = lib
TARGET = QMLDocumentSystem
QT += qml quick sql
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.mihail.qmldocumentsystem

INCLUDEPATH *= . \
    ./bin/ \
    ../../include/ \

LIB_LIST = \
    -lDossier \
    -lDocManager

LIBS += -L./bin/ \
    $${LIB_LIST}

# Input
SOURCES += \
    qmldocumentsystem_plugin.cpp \
    qmldocument.cpp \
    qmldocument_p.cpp \
    qmldocumentloader.cpp \
    qmldocumentpageprovider.cpp

HEADERS += \
    qmldocumentsystem_plugin.h \
    qmldocument.h \
    qmldocument_p.h \
    qmldocumentloader.h \
    qmldocumentpageprovider.h

OTHER_FILES = qmldir \
    QMLDocumentPage.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

QT_INSTALL_QML = C:/Qt/Qt5.1.0/5.1.0/mingw48_32/qml

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
