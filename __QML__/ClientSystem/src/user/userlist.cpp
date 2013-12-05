#include "userlist.h"

#include "userlist_p.h"


UserList::UserList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new UserList_P( this );
}

UserList::~UserList()
{
    while ( !p->m__Users.isEmpty() )
    {
        User *user = p->m__Users.takeFirst();
        disconnect( user, SIGNAL(destroyed()), this, SLOT(userDestroyed()) );
        delete user;
        user = NULL;
    }

    delete p;
    p = NULL;
}

int UserList::count() const
{
    return p->m__Users.count();
}

void UserList::clear() const
{
    while ( !p->m__Users.isEmpty() )
    {
        User *user = p->m__Users.takeFirst();
        disconnect( user, SIGNAL(destroyed()), this, SLOT(userDestroyed()) );
        delete user;
        user = NULL;
    }
    emit countChanged();
}

User * UserList::user( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Users[index];
}

int UserList::userIndex( User *user ) const
{
    return p->m__Users.indexOf( user );
}

User * UserList::addLink( User *link ) const
{
    if ( p->m__Users.contains( link ) ) return link;

    User *newUser = new User( p->p_dptr(), link );
    p->m__Users << newUser;
    connect( newUser, SIGNAL(destroyed()), SLOT(userDestroyed()) );
    emit userAdded( newUser );
    emit countChanged();
    return newUser;
}

User * UserList::find( QVariant identifier ) const
{
  foreach ( User *user, p->m__Users )
    if ( user->identifier() == identifier ) return user;

  return NULL;
}

void UserList::receivedUserInfo( UserInfo userInfo ) const
{
    User *newUser = new User( p->p_dptr(), userInfo );
    p->m__Users << newUser;
    connect( newUser, SIGNAL(destroyed()), SLOT(userDestroyed()) );
    emit userAdded( newUser );
    emit countChanged();
}

void UserList::userDestroyed()
{
    User *user = qobject_cast<User *>( sender() );
    int index = p->m__Users.indexOf( user );
    p->m__Users.removeAt( index );
    emit userRemoved( index );
    emit countChanged();
}
