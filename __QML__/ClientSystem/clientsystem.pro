TEMPLATE = lib
TARGET = ClientSystem
QT += qml quick sql
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.mihail.clientsystem

# Input
INCLUDEPATH += src/

SOURCES += \
    clientsystem_plugin.cpp \
    src/user/userlist.cpp \
    src/user/user.cpp \
    src/user/userlist_p.cpp \
    src/user/user_p.cpp \
    src/user/userinfo.cpp \
    src/user/userloader.cpp \
    src/user/userloader_p.cpp \
    src/procedure/procedureinfo.cpp \
    src/procedure/procedure.cpp \
    src/procedure/procedure_p.cpp \
    src/procedure/procedurelist.cpp \
    src/procedure/procedurelist_p.cpp \
    src/procedure/procedureloader.cpp \
    src/procedure/procedureloader_p.cpp \
    src/recipient/recipientinfo.cpp \
    src/recipient/recipient.cpp \
    src/recipient/recipient_p.cpp \
    src/recipient/recipientlist.cpp \
    src/recipient/recipientlist_p.cpp \
    src/recipient/recipientloader.cpp \
    src/recipient/recipientloader_p.cpp \
    src/department/departmentloader_p.cpp \
    src/department/departmentloader.cpp \
    src/department/departmentlist_p.cpp \
    src/department/departmentlist.cpp \
    src/department/departmentinfo.cpp \
    src/department/department_p.cpp \
    src/department/department.cpp \
    src/doctype/doctypeloader_p.cpp \
    src/doctype/doctypeloader.cpp \
    src/doctype/doctypelist_p.cpp \
    src/doctype/doctypelist.cpp \
    src/doctype/doctypeinfo.cpp \
    src/doctype/doctype_p.cpp \
    src/doctype/doctype.cpp

HEADERS += \
    clientsystem_plugin.h \
    src/user/userlist.h \
    src/user/user.h \
    src/user/userlist_p.h \
    src/user/user_p.h \
    src/user/userinfo.h \
    src/user/userloader.h \
    src/user/userloader_p.h \
    src/procedure/procedureinfo.h \
    src/procedure/procedure.h \
    src/procedure/procedure_p.h \
    src/procedure/procedurelist.h \
    src/procedure/procedurelist_p.h \
    src/procedure/procedureloader.h \
    src/procedure/procedureloader_p.h \
    src/recipient/recipientinfo.h \
    src/recipient/recipient.h \
    src/recipient/recipient_p.h \
    src/recipient/recipientlist.h \
    src/recipient/recipientlist_p.h \
    src/recipient/recipientloader.h \
    src/recipient/recipientloader_p.h \
    src/department/departmentloader_p.h \
    src/department/departmentloader.h \
    src/department/departmentlist_p.h \
    src/department/departmentlist.h \
    src/department/departmentinfo.h \
    src/department/department_p.h \
    src/department/department.h \
    src/doctype/doctypeloader_p.h \
    src/doctype/doctypeloader.h \
    src/doctype/doctypelist_p.h \
    src/doctype/doctypelist.h \
    src/doctype/doctypeinfo.h \
    src/doctype/doctype_p.h \
    src/doctype/doctype.h

OTHER_FILES = qmldir

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
