#include "clientsystem_plugin.h"

#include "user/user.h"
#include "user/userlist.h"
#include "user/userloader.h"
/// ============================================================================
#include "procedure/procedure.h"
#include "procedure/procedurelist.h"
#include "procedure/procedureloader.h"
/// ============================================================================
#include "recipient/recipient.h"
#include "recipient/recipientlist.h"
#include "recipient/recipientloader.h"
/// ============================================================================
#include "department/department.h"
#include "department/departmentlist.h"
#include "department/departmentloader.h"
/// ============================================================================
#include "doctype/doctype.h"
#include "doctype/doctypelist.h"
#include "doctype/doctypeloader.h"

#include <qqml.h>


void ClientSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.clientsystem

    /// About users
    qmlRegisterType<User>(uri, 1, 0, "User");
    qmlRegisterType<UserList>(uri, 1, 0, "UserList");
    qmlRegisterType<UserLoader>(uri, 1, 0, "UserLoader");

    /// About procedures
    qmlRegisterType<Procedure>(uri, 1, 0, "Procedure");
    qmlRegisterType<ProcedureList>(uri, 1, 0, "ProcedureList");
    qmlRegisterType<ProcedureLoader>(uri, 1, 0, "ProcedureLoader");

    /// About recipients
    qmlRegisterType<Recipient>(uri, 1, 0, "Recipient");
    qmlRegisterType<RecipientList>(uri, 1, 0, "RecipientList");
    qmlRegisterType<RecipientLoader>(uri, 1, 0, "RecipientLoader");

    /// About department
    qmlRegisterType<Department>(uri, 1, 0, "Department");
    qmlRegisterType<DepartmentList>(uri, 1, 0, "DepartmentList");
    qmlRegisterType<DepartmentLoader>(uri, 1, 0, "DepartmentLoader");

    /// About doctype
    qmlRegisterType<Doctype>(uri, 1, 0, "Doctype");
    qmlRegisterType<DoctypeList>(uri, 1, 0, "DoctypeList");
    qmlRegisterType<DoctypeLoader>(uri, 1, 0, "DoctypeLoader");
}


