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
/// ============================================================================
#include "callstatus/callstatus.h"
#include "callstatus/callstatuslist.h"
#include "callstatus/callstatusloader.h"
/// ============================================================================
#include "human/human.h"
#include "human/humanlist.h"
#include "human/humanloader.h"

#include <qqml.h>


void ClientSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.clientsystem

    /// About users
    qmlRegisterType<User>( uri, 1, 0, "User" );
    qmlRegisterType<UserList>( uri, 1, 0, "UserList" );
    qmlRegisterSingletonType<UserLoader>( uri, 1, 0, "UserLoader", userLoader_Provider );

    /// About procedures
    qmlRegisterType<Procedure>( uri, 1, 0, "Procedure" );
    qmlRegisterType<ProcedureList>( uri, 1, 0, "ProcedureList" );
    qmlRegisterSingletonType<ProcedureLoader>( uri, 1, 0, "ProcedureLoader", procedureLoader_Provider );

    /// About recipients
    qmlRegisterType<Recipient>( uri, 1, 0, "Recipient" );
    qmlRegisterType<RecipientList>( uri, 1, 0, "RecipientList" );
    qmlRegisterSingletonType<RecipientLoader>( uri, 1, 0, "RecipientLoader", recipientLoader_Provider );

    /// About departments
    qmlRegisterType<Department>( uri, 1, 0, "Department" );
    qmlRegisterType<DepartmentList>( uri, 1, 0, "DepartmentList" );
    qmlRegisterSingletonType<DepartmentLoader>( uri, 1, 0, "DepartmentLoader", departmentLoader_Provider );

    /// About doctypes
    qmlRegisterType<Doctype>( uri, 1, 0, "Doctype" );
    qmlRegisterType<DoctypeList>( uri, 1, 0, "DoctypeList" );
    qmlRegisterSingletonType<DoctypeLoader>( uri, 1, 0, "DoctypeLoader", doctypeLoader_Provider );

    /// About callstatuses
    qmlRegisterType<Callstatus>( uri, 1, 0, "Callstatus" );
    qmlRegisterType<CallstatusList>( uri, 1, 0, "CallstatusList" );
    qmlRegisterSingletonType<CallstatusLoader>( uri, 1, 0, "CallstatusLoader", callstatusLoader_Provider );

    /// About humans
    qmlRegisterType<Human>( uri, 1, 0, "Human" );
    qmlRegisterType<HumanList>( uri, 1, 0, "HumanList" );
    qmlRegisterSingletonType<HumanLoader>( uri, 1, 0, "HumanLoader", humanLoader_Provider );
}


