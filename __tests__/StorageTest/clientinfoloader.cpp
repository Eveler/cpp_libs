#include "clientinfoloader.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


ClientInfoLoader::ClientInfoLoader( const QString &connectionName, QObject *parent ) :
  QObject(parent)
{
  m__ConnectionName = connectionName;
}

void ClientInfoLoader::load( int declarId ) const
{
  QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
  if ( !db.open() )
  {
    emit databaseError( db.lastError().text() );
    return;
  }

  QSqlQuery qry( db );
  QString qryText = tr( "SELECT cl.clid, cl.clname, cl.addr, cl.phone"
                        " FROM declar_clients dc, clientlist cl"
                        " WHERE dc.client_id=cl.id AND dc.declar_id=%1" ).arg( declarId );
  if ( !qry.exec( qryText ) )
  {
    emit databaseError( qry.lastError().text() );
    return;
  }

  while ( qry.next() )
    emit clientInfoLoaded( qry.record().value( "clname" ).toString().replace(
                             "*|/|*", " " ).simplified(),
                           qry.record().value( "phone" ).toString() ,
                           qry.record().value( "addr" ).toString() ,
                           qry.record().value( "clid" ) );
}
