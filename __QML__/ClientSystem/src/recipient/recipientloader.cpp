#include "recipientloader.h"

#include "recipientloader_p.h"

#include <QSqlDatabase>


RecipientLoader::RecipientLoader(QObject *parent) :
    QObject(parent)
{
    p = new RecipientLoader_P( this );
    connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
    loop = new QEventLoop( this );
}

RecipientLoader::~RecipientLoader()
{
    p->m__Errors.clear();
    delete p;
    p = NULL;
}

QString RecipientLoader::error( int errorId ) const
{
    QString errorText = p->m__Errors.value( errorId, QString() );
    p->m__Errors.remove( errorId );
    return errorText;
}

const QString & RecipientLoader::connectionName() const
{
    if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
    {
        p->m__ConnectionName = QSqlDatabase::connectionNames().first();
        emit connectionNameChanged();
    }
    return p->m__ConnectionName;
}

bool RecipientLoader::setConnectionName( const QString &connectionName ) const
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

bool RecipientLoader::load() const
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

Recipient * RecipientLoader::create() const
{
    return NULL;
}

RecipientList * RecipientLoader::source() const
{
    return p->m__Source;
}

void RecipientLoader::setSource( RecipientList * source ) const
{
    if ( p->isRunning() )
    {
        receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
        return;
    }

    if ( p->m__Source != NULL )
        disconnect( p, SIGNAL(sendRecipientInfo(RecipientInfo)),
                    p->m__Source, SLOT(receivedRecipientInfo(RecipientInfo)) );

    p->m__Source = source;
    if ( p->m__Source != NULL )
        connect( p, SIGNAL(sendRecipientInfo(RecipientInfo)),
                 p->m__Source, SLOT(receivedRecipientInfo(RecipientInfo)) );
}

void RecipientLoader::threadFinished()
{
    loop->exit( ( p->m__Successfully ? 0 : 1 ) );
    emit finished();
}

void RecipientLoader::receivedError( QString errorText ) const
{
    int errorId = p->m__ErrorLastId++;
    p->m__Errors[errorId] = errorText;
    emit errorAdded( errorId );
}
