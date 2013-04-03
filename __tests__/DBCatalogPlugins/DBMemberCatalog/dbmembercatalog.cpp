#include "dbmembercatalog.h"


DBMemberCatalog::DBMemberCatalog() :
  DBCatalog_Interface()
{
}

QStringList DBMemberCatalog::categories() const
{
  return ( QStringList() << tr( "Пользователи" ) );
}

QWidget * DBMemberCatalog::createWidget( QWidget *parentWidget )
{
//  Widget_ProcessReport *result = new Widget_ProcessReport( parentWidget );
//  addWidget( result );
  return NULL;
}
