TEMPLATE = lib
TARGET = ClientSystem
QT += core qml quick sql
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.mihail.clientsystem

# Input
INCLUDEPATH += src/

SOURCES += \
    clientsystem_plugin.cpp \
    src/user/userinfo.cpp \
    src/user/userloader.cpp \
    src/user/userloader_p.cpp \
    src/procedure/procedureinfo.cpp \
    src/procedure/procedureloader.cpp \
    src/procedure/procedureloader_p.cpp \
    src/recipient/recipientinfo.cpp \
    src/recipient/recipientloader.cpp \
    src/recipient/recipientloader_p.cpp \
    src/department/departmentloader_p.cpp \
    src/department/departmentloader.cpp \
    src/department/departmentinfo.cpp \
    src/doctype/doctypeloader_p.cpp \
    src/doctype/doctypeloader.cpp \
    src/doctype/doctypeinfo.cpp \
    src/callstatus/callstatusloader_p.cpp \
    src/callstatus/callstatusloader.cpp \
    src/callstatus/callstatusinfo.cpp \
    src/human/humanloader_p.cpp \
    src/human/humanloader.cpp \
    src/human/humaninfo.cpp \
    src/clientprivatesystem.cpp \
    src/service/serviceloader_p.cpp \
    src/service/serviceloader.cpp \
    src/service/serviceinfo.cpp \
    src/organisation/organisationloader_p.cpp \
    src/organisation/organisationloader.cpp \
    src/organisation/organisationinfo.cpp \
    src/client/clientloader_p.cpp \
    src/client/clientloader.cpp \
    src/client/clientinfo.cpp \
    src/trustee/trusteeloader_p.cpp \
    src/trustee/trusteeloader.cpp \
    src/trustee/trusteeinfo.cpp \
    src/declarclient/declarclientloader_p.cpp \
    src/declarclient/declarclientloader.cpp \
    src/declarclient/declarclientinfo.cpp \
    src/declar/declarloader_p.cpp \
    src/declar/declarloader.cpp \
    src/declar/declarinfo.cpp \
    src/result/resultloader_p.cpp \
    src/result/resultloader.cpp \
    src/result/resultinfo.cpp \
    src/resultway/resultwayloader_p.cpp \
    src/resultway/resultwayloader.cpp \
    src/resultway/resultwayinfo.cpp \
    src/assessment/assessmentloader_p.cpp \
    src/assessment/assessmentloader.cpp \
    src/assessment/assessmentinfo.cpp \
    src/assessmenttype/assessmenttypeloader_p.cpp \
    src/assessmenttype/assessmenttypeloader.cpp \
    src/assessmenttype/assessmenttypeinfo.cpp

HEADERS += \
    clientsystem_plugin.h \
    src/user/userinfo.h \
    src/user/userloader.h \
    src/user/userloader_p.h \
    src/procedure/procedureinfo.h \
    src/procedure/procedureloader.h \
    src/procedure/procedureloader_p.h \
    src/recipient/recipientinfo.h \
    src/recipient/recipientloader.h \
    src/recipient/recipientloader_p.h \
    src/department/departmentloader_p.h \
    src/department/departmentloader.h \
    src/department/departmentinfo.h \
    src/doctype/doctypeloader_p.h \
    src/doctype/doctypeloader.h \
    src/doctype/doctypeinfo.h \
    src/callstatus/callstatusloader_p.h \
    src/callstatus/callstatusloader.h \
    src/callstatus/callstatusinfo.h \
    src/human/humanloader_p.h \
    src/human/humanloader.h \
    src/human/humaninfo.h \
    src/clientprivatesystem.h \
    src/service/serviceloader_p.h \
    src/service/serviceloader.h \
    src/service/serviceinfo.h \
    src/organisation/organisationloader_p.h \
    src/organisation/organisationloader.h \
    src/organisation/organisationinfo.h \
    src/client/clientloader_p.h \
    src/client/clientloader.h \
    src/client/clientinfo.h \
    src/trustee/trusteeloader_p.h \
    src/trustee/trusteeloader.h \
    src/trustee/trusteeinfo.h \
    src/declarclient/declarclientloader_p.h \
    src/declarclient/declarclientloader.h \
    src/declarclient/declarclientinfo.h \
    src/declar/declarloader_p.h \
    src/declar/declarloader.h \
    src/declar/declarinfo.h \
    src/result/resultloader_p.h \
    src/result/resultloader.h \
    src/result/resultinfo.h \
    src/resultway/resultwayloader_p.h \
    src/resultway/resultwayloader.h \
    src/resultway/resultwayinfo.h \
    src/assessment/assessmentloader_p.h \
    src/assessment/assessmentloader.h \
    src/assessment/assessmentinfo.h \
    src/assessmenttype/assessmenttypeloader_p.h \
    src/assessmenttype/assessmenttypeloader.h \
    src/assessmenttype/assessmenttypeinfo.h

OTHER_FILES = qmldir \
    qml/Assessment.qml \
    qml/Assessmenttype.qml \
    qml/Callstatus.qml \
    qml/ClientSystemSources.qml \
    qml/Client.qml \
    qml/Declar.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

QT_INSTALL_QML = C:/Qt/Qt5.2.0/5.2.0/mingw48_32/qml

qmldir.files = $$OTHER_FILES
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
