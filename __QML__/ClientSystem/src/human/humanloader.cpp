#include "humanloader.h"

#include "humanloader_p.h"

#include <QSqlDatabase>


HumanLoader::HumanLoader(QObject *parent) :
    QObject(parent)
{
    p = new HumanLoader_P( this );
    newSource();
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

HumanLoader::~HumanLoader()
{
    p->m__Errors.clear();
    disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(newSource()) );
    delete p;
    p = NULL;
}

QString HumanLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & HumanLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool HumanLoader::setConnectionName( const QString &connectionName ) const
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

bool HumanLoader::load() const
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

Human * HumanLoader::create() const
{
    return NULL;
}

HumanList * HumanLoader::source() const
{
    return p->m__Source;
}

void HumanLoader::newSource() const
{
    p->m__Source = new HumanList( p->p_dptr() );
    connect( p->m__Source, SIGNAL(destroyed()), SLOT(newSource()) );
    connect( p, SIGNAL(sendHumanInfo(HumanInfo)),
             p->m__Source, SLOT(receivedHumanInfo(HumanInfo)) );
}

void HumanLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void HumanLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
