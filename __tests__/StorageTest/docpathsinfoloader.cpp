#include "docpathsinfoloader.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


DocpathsInfoLoader::DocpathsInfoLoader( const QString &connectionName, QObject *parent ) :
  QObject(parent)
{
  m__ConnectionName = connectionName;
}

void DocpathsInfoLoader::load( int declarId ) const
{
  QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
  if ( !db.open() )
  {
    emit databaseError( db.lastError().text() );
    return;
  }

  QSqlQuery qry( db );
  QString qryText = tr( "SELECT dp.id"
                        " FROM docpaths dp"
                        " WHERE dp.declarid=%1" ).arg( declarId );
  if ( !qry.exec( qryText ) )
  {
    emit databaseError( qry.lastError().text() );
    return;
  }

  while ( qry.next() )
    emit docpathInfoLoaded( qry.record().value( "id" ) );
}
