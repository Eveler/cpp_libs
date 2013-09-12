#include "procedureloader.h"

#include "procedureloader_p.h"

#include <QSqlDatabase>


ProcedureLoader::ProcedureLoader(QObject *parent) :
    QObject(parent)
{
    p = new ProcedureLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

ProcedureLoader::~ProcedureLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString ProcedureLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & ProcedureLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool ProcedureLoader::setConnectionName( const QString &connectionName ) const
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

bool ProcedureLoader::load() const
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

Procedure * ProcedureLoader::create() const
{
    return NULL;
}

ProcedureList * ProcedureLoader::source() const
{
    return p->m__Source;
}

void ProcedureLoader::setSource( ProcedureList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendProcedureInfo(ProcedureInfo)),
                    p->m__Source, SLOT(receivedProcedureInfo(ProcedureInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendProcedureInfo(ProcedureInfo)),
                 p->m__Source, SLOT(receivedProcedureInfo(ProcedureInfo)) );
}

void ProcedureLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void ProcedureLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
