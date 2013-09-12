#include "doctypeloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void DoctypeLoader_P::run()
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
    if ( !qry.exec( tr( "SELECT id AS identifier, aname AS name"
                        " FROM doctypes ORDER BY aname" ) ) )
    {
        m__Successfully = false;
        emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
        return;
    }
    while ( qry.next() )
    {
        DoctypeInfo info;
        info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
        info.setName( qry.record().value( tr( "name" ) ).toString() );
        emit sendDoctypeInfo( info );
    }
}

DoctypeLoader_P::DoctypeLoader_P( DoctypeLoader *parent ) :
    QThread(parent),
    m__Successfully(true),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Source(NULL)
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    qRegisterMetaType<DoctypeInfo>("DoctypeInfo");
}

DoctypeLoader_P::~DoctypeLoader_P()
{
    m__Source = NULL;
}

DoctypeLoader * DoctypeLoader_P::p_dptr() const
{
    return qobject_cast<DoctypeLoader *>( parent() );
}
