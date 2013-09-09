#include "user.h"

#include "userlist.h"


User::User( UserList *parent ) :
    QObject(parent)
{
}

User::User( UserList *parent, const User &other ) :
    QObject(parent)
{

}

User::User( UserList *parent, User *link ) :
    QObject(parent)
{

}

User::~User()
{

}

UserList * User::userList() const
{
    return qobject_cast<UserList *>( parent() );
}

void User::resetIndex()
{

}
