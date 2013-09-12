#include "departmentloader.h"

#include "departmentloader_p.h"

#include <QSqlDatabase>


DepartmentLoader::DepartmentLoader(QObject *parent) :
    QObject(parent)
{
    p = new DepartmentLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

DepartmentLoader::~DepartmentLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString DepartmentLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & DepartmentLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool DepartmentLoader::setConnectionName( const QString &connectionName ) const
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

bool DepartmentLoader::load() const
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

Department * DepartmentLoader::create() const
{
    return NULL;
}

DepartmentList * DepartmentLoader::source() const
{
    return p->m__Source;
}

void DepartmentLoader::setSource( DepartmentList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendDepartmentInfo(DepartmentInfo)),
                    p->m__Source, SLOT(receivedDepartmentInfo(DepartmentInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendDepartmentInfo(DepartmentInfo)),
                 p->m__Source, SLOT(receivedDepartmentInfo(DepartmentInfo)) );
}

void DepartmentLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void DepartmentLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
