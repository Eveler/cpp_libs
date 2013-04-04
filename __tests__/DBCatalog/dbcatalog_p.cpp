#include "dbcatalog_p.h"

#include "dbcatalog.h"
#include "ui_dbcatalog.h"
#include "widget_configuration.h"

#include <QMdiSubWindow>


DBCatalog_P::DBCatalog_P( DBCatalog *parent ) :
  QObject(parent)
{
  m__Configuration = new Widget_Configuration( parent->ui->menu_Tools, parent );
//  m__Configuration->setWindowFlags( Qt::Window );
//  m__Configuration->setWindowModality( Qt::WindowModal );
  connect( m__Configuration, SIGNAL(pluginWidgetCreated(QWidget*)), SLOT(showPluginWidget(QWidget*)) );
}

DBCatalog_P::~DBCatalog_P()
{
  delete m__Configuration;
  m__Configuration = NULL;
}

DBCatalog * DBCatalog_P::p_dptr() const
{
  return qobject_cast<DBCatalog *>( parent() );
}

void DBCatalog_P::showConfiguration()
{
  m__Configuration->exec();
}

void DBCatalog_P::showPluginWidget( QWidget *widget )
{
  p_dptr()->ui->mdiArea->addSubWindow( widget )->showMaximized();
}

