#include "userloader.h"

#include "userloader_p.h"

#include <QSqlDatabase>


UserLoader::UserLoader(QObject *parent) :
    QObject(parent)
{
    p = new UserLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

UserLoader::~UserLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString UserLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & UserLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool UserLoader::setConnectionName( const QString &connectionName ) const
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

bool UserLoader::load() const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return false;
    }

    emit started();
    p->m__Source->clear();
    p->start();
    return ( loop->exec() == 0 );
}

User * UserLoader::create() const
{
    return NULL;
}

UserList * UserLoader::source() const
{
    return p->m__Source;
}

void UserLoader::setSource( UserList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendUserInfo(UserInfo)),
                    p->m__Source, SLOT(receivedUserInfo(UserInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendUserInfo(UserInfo)),
                 p->m__Source, SLOT(receivedUserInfo(UserInfo)) );
}

void UserLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void UserLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
