#include "dbmembercatalog.h"


DBMemberCatalog::DBMemberCatalog() :
  DBCatalog_Interface()
{
}

QStringList DBMemberCatalog::categories() const
{
  return ( QStringList() << tr( "Пользователи" ) );
}

QWidget * DBMemberCatalog::createMainWidget( QWidget *parentWidget )
{
//  Widget_ProcessReport *result = new Widget_ProcessReport( parentWidget );
//  addWidget( result );
  return NULL;
}

QWidget * DBMemberCatalog::createConfWidget( QWidget *parentWidget )
{
//  Widget_ProcessReport *result = new Widget_ProcessReport( parentWidget );
//  addWidget( result );
  return NULL;
}
