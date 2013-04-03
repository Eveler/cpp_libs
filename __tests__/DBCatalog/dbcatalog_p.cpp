#include "dbcatalog_p.h"

#include "dbcatalog.h"
#include "ui_dbcatalog.h"
#include "widget_configuration.h"

#include <QMdiSubWindow>


DBCatalog_P::DBCatalog_P( DBCatalog *parent ) :
  QObject(parent)
{
}

DBCatalog_P::~DBCatalog_P()
{
}

DBCatalog * DBCatalog_P::p_dptr() const
{
  return qobject_cast<DBCatalog *>( parent() );
}

void DBCatalog_P::showPluginWidget( QWidget *widget )
{
  p_dptr()->ui->mdiArea->addSubWindow( widget )->showMaximized();
}

