#include "user.h"

#include "user_p.h"
#include "userlist.h"


User::User( UserList *parent ) :
    QObject(parent), UserInfo()
{
    p = new User_P( this );
}

User::User( UserList *parent, const UserInfo &info ) :
    QObject(parent), UserInfo()
{
    p = new User_P( this );
}

User::User( UserList *parent, User *link ) :
    QObject(parent), UserInfo()
{
    p = new User_P( this );
}

User::~User()
{
    delete p;
    p = NULL;
}

UserList * User::userList() const
{
    return qobject_cast<UserList *>( parent() );
}

int User::index() const
{
    UserList *ul = userList();
    if ( ul == NULL ) return -1;

    return ul->userIndex( p->p_dptr() );
}

void User::setIdentifier( QVariant identifier )
{
    UserInfo *info = static_cast<UserInfo *>( p->p_dptr() );
    info->setIdentifier( identifier );
    emit identifierChanged();
}

void User::resetIndex()
{

}
