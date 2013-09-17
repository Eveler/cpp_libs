#include "humanloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void HumanLoader_P::run()
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
    if ( !qry.exec( tr( "SELECT id AS identifier, surname, firstname, lastname"
                        " FROM humans ORDER BY surname, firstname, lastname" ) ) )
    {
        m__Successfully = false;
        emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
        return;
    }
    while ( qry.next() )
    {
        HumanInfo info;
        info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
        info.setSurname( qry.record().value( tr( "surname" ) ).toString() );
        info.setFirstname( qry.record().value( tr( "firstname" ) ).toString() );
        info.setLastname( qry.record().value( tr( "lastname" ) ).toString() );
        emit sendHumanInfo( info );
    }
}

HumanLoader_P::HumanLoader_P( HumanLoader *parent ) :
    QThread(parent),
    m__Successfully(true),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Source(NULL)
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    qRegisterMetaType<HumanInfo>("HumanInfo");
}

HumanLoader_P::~HumanLoader_P()
{
    delete m__Source;
    m__Source = NULL;
}

HumanLoader * HumanLoader_P::p_dptr() const
{
    return qobject_cast<HumanLoader *>( parent() );
}
