#include "userlist_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void UserList_P::run()
{
    m__Successfully = true;
    QSqlDatabase db = QSqlDatabase::database( p_dptr()->connectionName() );
    if ( !db.isValid() )
    {
        m__Successfully = false;
        emit sendError( tr( "Database with name [%1] is not valid." ).arg( db.connectionName() ) );
        return;
    }
    if ( db.lastError().isValid() )
    {
        m__Successfully = false;
        emit sendError( tr( "Database error:\n%1" ).arg( db.lastError().text() ) );
        return;
    }
    if ( !db.isOpen() )
    {
        m__Successfully = false;
        emit sendError( tr( "Database open error." ) );
        return;
    }
    QSqlQuery qry( db );
    if ( !qry.exec( tr( "SELECT id AS identifier, surname, aname AS firstname,"
                        " lastname FROM users ORDER BY surname, aname, lastname" ) ) )
    {
        m__Successfully = false;
        emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
        return;
    }
    while ( qry.next() )
    {
        UserInfo info;
        info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
        info.setSurname( qry.record().value( tr( "surname" ) ).toString() );
        info.setFirstname( qry.record().value( tr( "firstname" ) ).toString() );
        info.setLastname( qry.record().value( tr( "lastname" ) ).toString() );
        emit sendUserInfo( info );
    }
}

UserList_P::UserList_P( UserList *parent ) :
    QThread(parent),
    m__Successfully(true),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Users(QList<User *>())
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    qRegisterMetaType<UserInfo>( "UserInfo" );
    connect( this, SIGNAL(sendUserInfo(UserInfo)), parent, SLOT(receivedUserInfo(UserInfo)) );
}

UserList_P::~UserList_P()
{
}

UserList * UserList_P::p_dptr() const
{
    return qobject_cast<UserList *>( parent() );
}

