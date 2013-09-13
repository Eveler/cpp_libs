#include "callstatusloader.h"

#include "callstatusloader_p.h"

#include <QSqlDatabase>


CallstatusLoader::CallstatusLoader(QObject *parent) :
    QObject(parent)
{
    p = new CallstatusLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

CallstatusLoader::~CallstatusLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString CallstatusLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & CallstatusLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool CallstatusLoader::setConnectionName( const QString &connectionName ) const
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

bool CallstatusLoader::load() const
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

Callstatus * CallstatusLoader::create() const
{
    return NULL;
}

CallstatusList * CallstatusLoader::source() const
{
    return p->m__Source;
}

void CallstatusLoader::setSource( CallstatusList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendCallstatusInfo(CallstatusInfo)),
                    p->m__Source, SLOT(receivedCallstatusInfo(CallstatusInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendCallstatusInfo(CallstatusInfo)),
                 p->m__Source, SLOT(receivedCallstatusInfo(CallstatusInfo)) );
}

void CallstatusLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void CallstatusLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
