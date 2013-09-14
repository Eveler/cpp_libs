#include "callstatusloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void CallstatusLoader_P::run()
{
    m__Successfully = true;
    QSqlDatabase db = QSqlDatabase::database( p_dptr()->connectionName(), false );
    db.open();
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
    if ( !qry.exec( tr( "SELECT id AS identifier, status AS name"
                        " FROM call_statuses ORDER BY status" ) ) )
    {
        m__Successfully = false;
        emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
        return;
    }
    while ( qry.next() )
    {
        CallstatusInfo info;
        info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
        info.setName( qry.record().value( tr( "name" ) ).toString() );
        emit sendCallstatusInfo( info );
    }
}

CallstatusLoader_P::CallstatusLoader_P( CallstatusLoader *parent ) :
    QThread(parent),
    m__Successfully(true),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Source(NULL)
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    qRegisterMetaType<CallstatusInfo>("CallstatusInfo");
}

CallstatusLoader_P::~CallstatusLoader_P()
{
    delete m__Source;
    m__Source = NULL;
}

CallstatusLoader * CallstatusLoader_P::p_dptr() const
{
    return qobject_cast<CallstatusLoader *>( parent() );
}
