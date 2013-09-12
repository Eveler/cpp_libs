#include "clientsystem_plugin.h"

#include "user/user.h"
#include "user/userlist.h"
#include "user/userloader.h"
/// ============================================================================
#include "procedure/procedure.h"
#include "procedure/procedurelist.h"
#include "procedure/procedureloader.h"

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
}


