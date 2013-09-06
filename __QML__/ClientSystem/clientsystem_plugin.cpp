#include "clientsystem_plugin.h"
#include "user/userlist.h"

#include <qqml.h>

void ClientSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.clientsystem
    qmlRegisterType<UserList>(uri, 1, 0, "UserList");
    qmlRegisterType<User>(uri, 1, 0, "User");
}


