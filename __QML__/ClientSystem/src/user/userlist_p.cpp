#include "userlist_p.h"


UserList_P::UserList_P( UserList *parent ) :
    QObject(parent),
    m__Users(QList<User *>())
{
}

UserList_P::~UserList_P()
{
}

UserList * UserList_P::p_dptr() const
{
    return qobject_cast<UserList *>( parent() );
}

