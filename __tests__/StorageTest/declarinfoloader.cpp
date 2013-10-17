#include "declarinfoloader.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


DeclarInfoLoader::DeclarInfoLoader(const QString & connectionName, QObject *parent) :
  QObject(parent)
{
  m__ConnectionName = connectionName;
}

void DeclarInfoLoader::load( int declarNum ) const
{
  QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
  if ( !db.open() )
  {
    emit databaseError( db.lastError().text() );
    return;
  }

  QSqlQuery qry( db );
  QString qryText = tr( "SELECT d.id, d.srvid"
                        " FROM declars d"
                        " WHERE d.declarnum=%1" ).arg( declarNum );
  if ( !qry.exec( qryText ) )
  {
    emit databaseError( qry.lastError().text() );
    return;
  }

  while ( qry.next() )
    emit declarInfoLoaded( qry.record().value( "id" ),
                           qry.record().value( "srvid" ) );
}
