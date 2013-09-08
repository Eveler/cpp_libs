#include "userlist.h"

#include "userlist_p.h"

#include <QSqlDatabase>


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
    p->m__Errors.clear();
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

QString UserList::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & UserList::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool UserList::setConnectionName( const QString &connectionName ) const
{
    if ( !QSqlDatabase::contains( connectionName ) )
    {
        QString connection = this->connectionName();
        if ( connection.isEmpty() ) return false;
    }
    else
    {
        p->m__ConnectionName = connectionName;
        emit connectionNameChanged();
    }
    return true;
}

bool UserList::load() const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return false;
    }

    p->start();
    return true;
}

int UserList::count() const
{
    return p->m__Users.count();
}

User * UserList::user( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Users[index];
}

void UserList::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}

void UserList::receivedUser( User *user ) const
{
    User *newUser = new User( p->p_dptr(), user );
    delete user;
    user = NULL;
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
