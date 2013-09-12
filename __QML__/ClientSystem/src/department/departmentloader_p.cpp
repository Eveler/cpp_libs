#include "departmentloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void DepartmentLoader_P::run()
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
                        " FROM departments ORDER BY aname" ) ) )
    {
        m__Successfully = false;
        emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
        return;
    }
    while ( qry.next() )
    {
        DepartmentInfo info;
        info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
        info.setName( qry.record().value( tr( "name" ) ).toString() );
        emit sendDepartmentInfo( info );
    }
}

DepartmentLoader_P::DepartmentLoader_P( DepartmentLoader *parent ) :
    QThread(parent),
    m__Successfully(true),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Source(NULL)
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    qRegisterMetaType<DepartmentInfo>("DepartmentInfo");
}

DepartmentLoader_P::~DepartmentLoader_P()
{
    m__Source = NULL;
}

DepartmentLoader * DepartmentLoader_P::p_dptr() const
{
    return qobject_cast<DepartmentLoader *>( parent() );
}
