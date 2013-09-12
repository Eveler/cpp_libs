#include "doctypeloader.h"

#include "doctypeloader_p.h"

#include <QSqlDatabase>


DoctypeLoader::DoctypeLoader(QObject *parent) :
    QObject(parent)
{
    p = new DoctypeLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

DoctypeLoader::~DoctypeLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString DoctypeLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & DoctypeLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool DoctypeLoader::setConnectionName( const QString &connectionName ) const
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

bool DoctypeLoader::load() const
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

Doctype * DoctypeLoader::create() const
{
    return NULL;
}

DoctypeList * DoctypeLoader::source() const
{
    return p->m__Source;
}

void DoctypeLoader::setSource( DoctypeList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendDoctypeInfo(DoctypeInfo)),
                    p->m__Source, SLOT(receivedDoctypeInfo(DoctypeInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendDoctypeInfo(DoctypeInfo)),
                 p->m__Source, SLOT(receivedDoctypeInfo(DoctypeInfo)) );
}

void DoctypeLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void DoctypeLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
