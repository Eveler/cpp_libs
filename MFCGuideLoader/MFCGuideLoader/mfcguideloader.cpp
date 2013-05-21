#include "mfcguideloader.h"

#include "direction.h"
#include "directionsstorage.h"
#include "post.h"
#include "postsstorage.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


QString MFCGuideLoader::m__ConnectionName = QString();

bool MFCGuideLoader::setConnectionName( QString connectionName )
{
  if ( !QSqlDatabase::contains( connectionName ) ) return false;

  m__ConnectionName = connectionName;

  return true;
}

QString MFCGuideLoader::connectionName()
{
  return m__ConnectionName;
}

Direction * MFCGuideLoader::loadDirection( int id, QString *error )
{
  DirectionsStorage *directionsStorage = DirectionsStorage::instance();
  AbstractSimpleObjectList res = directionsStorage->findById( directionsStorage->objects(), id );
  if ( !res.isEmpty() )
    return qobject_cast<Direction *>( res.first() );


  Direction *result = NULL;

  QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
  if ( !db.isValid() )
  {
    if ( error != NULL )
      *error = QObject::tr( "Database is not valid!" );
    return result;
  }

  QString sqlText = QObject::tr( "SELECT dirv.* FROM direction_s.directions_view dirv"
                                 " WHERE dirv.\"ID АЕ\"=%1" ).arg( id );
  QSqlQuery qry;
  if ( !qry.exec( sqlText ) )
  {
    if ( error != NULL )
      *error = qry.lastError().text();
    return result;
  }
  else if ( !qry.next() ) return result;

  Direction *parentDirection = NULL;
  if ( qry.record().value( QObject::tr( "ID начальствующей АЕ" ) ).isValid() )
  {
    parentDirection = loadDirection(
          qry.record().value( QObject::tr( "ID начальствующей АЕ" ) ).toInt(), error );
    if ( parentDirection == NULL ) return result;
  }

  result = qobject_cast<Direction *>( directionsStorage->addObject( id ) );
  result->setName( qry.record().value( QObject::tr( "Наименование АЕ" ) ).toString() );
  if ( parentDirection != NULL ) parentDirection->addChildDirection( result );

  return result;
}

Post * MFCGuideLoader::loadPost( int id, QString *error )
{
  PostsStorage *postsStorage = PostsStorage::instance();
  AbstractSimpleObjectList res = postsStorage->findById( postsStorage->objects(), id );
  if ( !res.isEmpty() )
    return qobject_cast<Post *>( res.first() );


  Post *result = NULL;

  QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
  if ( !db.isValid() )
  {
    if ( error != NULL )
      *error = QObject::tr( "Database is not valid!" );
    return result;
  }

  QString sqlText = QObject::tr( "SELECT postv.* FROM post_s.posts_view postv"
                                 " WHERE postv.\"ID должности\"=%1" ).arg( id );
  QSqlQuery qry;
  if ( !qry.exec( sqlText ) )
  {
    if ( error != NULL )
      *error = qry.lastError().text();
    return result;
  }
  else if ( !qry.next() ) return result;

  Direction *direction = loadDirection(
        qry.record().value( QObject::tr( "ID АЕ" ) ).toInt(), error );
  if ( direction == NULL ) return result;

  result = qobject_cast<Post *>( postsStorage->addObject( id ) );
  result->setName( qry.record().value( QObject::tr( "Наименование должности" ) ).toString() );
  result->setDirection( direction );

  return result;
}

