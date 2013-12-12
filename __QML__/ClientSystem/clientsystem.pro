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
    src/doctype/doctype.cpp \
    src/callstatus/callstatusloader_p.cpp \
    src/callstatus/callstatusloader.cpp \
    src/callstatus/callstatuslist_p.cpp \
    src/callstatus/callstatuslist.cpp \
    src/callstatus/callstatusinfo.cpp \
    src/callstatus/callstatus_p.cpp \
    src/callstatus/callstatus.cpp \
    src/human/humanloader_p.cpp \
    src/human/humanloader.cpp \
    src/human/humanlist_p.cpp \
    src/human/humanlist.cpp \
    src/human/humaninfo.cpp \
    src/human/human_p.cpp \
    src/human/human.cpp \
    src/clientprivatesystem.cpp \
    src/service/serviceloader_p.cpp \
    src/service/serviceloader.cpp \
    src/service/servicelist_p.cpp \
    src/service/servicelist.cpp \
    src/service/serviceinfo.cpp \
    src/service/service_p.cpp \
    src/service/service.cpp \
    src/organisation/organisationloader_p.cpp \
    src/organisation/organisationloader.cpp \
    src/organisation/organisationlist_p.cpp \
    src/organisation/organisationlist.cpp \
    src/organisation/organisationinfo.cpp \
    src/organisation/organisation_p.cpp \
    src/organisation/organisation.cpp \
    src/client/clientloader_p.cpp \
    src/client/clientloader.cpp \
    src/client/clientlist_p.cpp \
    src/client/clientlist.cpp \
    src/client/clientinfo.cpp \
    src/client/client_p.cpp \
    src/client/client.cpp \
    src/trustee/trusteeloader_p.cpp \
    src/trustee/trusteeloader.cpp \
    src/trustee/trusteelist_p.cpp \
    src/trustee/trusteelist.cpp \
    src/trustee/trusteeinfo.cpp \
    src/trustee/trustee_p.cpp \
    src/trustee/trustee.cpp \
    src/declarclient/declarclientloader_p.cpp \
    src/declarclient/declarclientloader.cpp \
    src/declarclient/declarclientlist_p.cpp \
    src/declarclient/declarclientlist.cpp \
    src/declarclient/declarclientinfo.cpp \
    src/declarclient/declarclient_p.cpp \
    src/declarclient/declarclient.cpp \
    src/declar/declarloader_p.cpp \
    src/declar/declarloader.cpp \
    src/declar/declarlist_p.cpp \
    src/declar/declarlist.cpp \
    src/declar/declarinfo.cpp \
    src/declar/declar_p.cpp \
    src/declar/declar.cpp \
    src/result/resultloader_p.cpp \
    src/result/resultloader.cpp \
    src/result/resultlist_p.cpp \
    src/result/resultlist.cpp \
    src/result/resultinfo.cpp \
    src/result/result_p.cpp \
    src/result/result.cpp \
    src/resultway/resultwayloader_p.cpp \
    src/resultway/resultwayloader.cpp \
    src/resultway/resultwaylist_p.cpp \
    src/resultway/resultwaylist.cpp \
    src/resultway/resultwayinfo.cpp \
    src/resultway/resultway_p.cpp \
    src/resultway/resultway.cpp \
    src/assessment/assessmentloader_p.cpp \
    src/assessment/assessmentloader.cpp \
    src/assessment/assessmentlist_p.cpp \
    src/assessment/assessmentlist.cpp \
    src/assessment/assessmentinfo.cpp \
    src/assessment/assessment_p.cpp \
    src/assessment/assessment.cpp \
    src/assessmenttype/assessmenttypeloader_p.cpp \
    src/assessmenttype/assessmenttypeloader.cpp \
    src/assessmenttype/assessmenttypelist_p.cpp \
    src/assessmenttype/assessmenttypelist.cpp \
    src/assessmenttype/assessmenttypeinfo.cpp \
    src/assessmenttype/assessmenttype_p.cpp \
    src/assessmenttype/assessmenttype.cpp

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
    src/doctype/doctype.h \
    src/callstatus/callstatusloader_p.h \
    src/callstatus/callstatusloader.h \
    src/callstatus/callstatuslist_p.h \
    src/callstatus/callstatuslist.h \
    src/callstatus/callstatusinfo.h \
    src/callstatus/callstatus_p.h \
    src/callstatus/callstatus.h \
    src/human/humanloader_p.h \
    src/human/humanloader.h \
    src/human/humanlist_p.h \
    src/human/humanlist.h \
    src/human/humaninfo.h \
    src/human/human_p.h \
    src/human/human.h \
    src/clientprivatesystem.h \
    src/service/serviceloader_p.h \
    src/service/serviceloader.h \
    src/service/servicelist_p.h \
    src/service/servicelist.h \
    src/service/serviceinfo.h \
    src/service/service_p.h \
    src/service/service.h \
    src/organisation/organisationloader_p.h \
    src/organisation/organisationloader.h \
    src/organisation/organisationlist_p.h \
    src/organisation/organisationlist.h \
    src/organisation/organisationinfo.h \
    src/organisation/organisation_p.h \
    src/organisation/organisation.h \
    src/client/clientloader_p.h \
    src/client/clientloader.h \
    src/client/clientlist_p.h \
    src/client/clientlist.h \
    src/client/clientinfo.h \
    src/client/client_p.h \
    src/client/client.h \
    src/trustee/trusteeloader_p.h \
    src/trustee/trusteeloader.h \
    src/trustee/trusteelist_p.h \
    src/trustee/trusteelist.h \
    src/trustee/trusteeinfo.h \
    src/trustee/trustee_p.h \
    src/trustee/trustee.h \
    src/declarclient/declarclientloader_p.h \
    src/declarclient/declarclientloader.h \
    src/declarclient/declarclientlist_p.h \
    src/declarclient/declarclientlist.h \
    src/declarclient/declarclientinfo.h \
    src/declarclient/declarclient_p.h \
    src/declarclient/declarclient.h \
    src/declar/declarloader_p.h \
    src/declar/declarloader.h \
    src/declar/declarlist_p.h \
    src/declar/declarlist.h \
    src/declar/declarinfo.h \
    src/declar/declar_p.h \
    src/declar/declar.h \
    src/result/resultloader_p.h \
    src/result/resultloader.h \
    src/result/resultlist_p.h \
    src/result/resultlist.h \
    src/result/resultinfo.h \
    src/result/result_p.h \
    src/result/result.h \
    src/resultway/resultwayloader_p.h \
    src/resultway/resultwayloader.h \
    src/resultway/resultwaylist_p.h \
    src/resultway/resultwaylist.h \
    src/resultway/resultwayinfo.h \
    src/resultway/resultway_p.h \
    src/resultway/resultway.h \
    src/assessment/assessmentloader_p.h \
    src/assessment/assessmentloader.h \
    src/assessment/assessmentlist_p.h \
    src/assessment/assessmentlist.h \
    src/assessment/assessmentinfo.h \
    src/assessment/assessment_p.h \
    src/assessment/assessment.h \
    src/assessmenttype/assessmenttypeloader_p.h \
    src/assessmenttype/assessmenttypeloader.h \
    src/assessmenttype/assessmenttypelist_p.h \
    src/assessmenttype/assessmenttypelist.h \
    src/assessmenttype/assessmenttypeinfo.h \
    src/assessmenttype/assessmenttype_p.h \
    src/assessmenttype/assessmenttype.h

OTHER_FILES = qmldir \
    qml/LoaderErrors.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

QT_INSTALL_QML = C:/Qt/Qt5.1.0/5.1.0/mingw48_32/qml

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
