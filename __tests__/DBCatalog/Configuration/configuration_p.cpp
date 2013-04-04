#include "configuration_p.h"

#include "widget_configuration.h"
#include "ui_widget_configuration.h"
#include "dbcatalog_interface.h"
#include "amslogger.h"
#include "mwidgetscore.h"
#include "mfccore.h"

#include <QMainWindow>
#include <QFileInfoList>
#include <QDir>
#include <QPluginLoader>
#include <QMenu>


#define KEY__PLUGIN_SOURCES tr( "PLUGINS/Sources" )
#define KEY__PLUGIN_INSTALL tr( "PLUGINS/Install" )

#define PLUGINS_PATH qApp->applicationDirPath()+tr( "/plugins" )


Configuration_P::Configuration_P( QMenu *menuPlugins, Widget_Configuration *parent ) :
  QObject(parent)
{
  m__MenuPlugins = menuPlugins;

  loadConfiguration();

  updatePlugins();
}

Configuration_P::~Configuration_P()
{
  while ( !m__Plugins.isEmpty() )
    unloadPlugin( m__Plugins.first() );

  m__MenuPlugins = NULL;
}

Widget_Configuration * Configuration_P::p_dptr() const
{
  return qobject_cast<Widget_Configuration *>( parent() );
}

QPluginLoader * Configuration_P::plugin( const QFileInfo &fileInfo )
{
  foreach ( QPluginLoader *pl, m__Plugins )
    if ( pl->fileName() == fileInfo.path()+"/"+fileInfo.fileName() )
      return pl;

  return NULL;
}

void Configuration_P::loadPlugin( const QFileInfo &fileInfo )
{
  QPluginLoader *pl = new QPluginLoader( fileInfo.path()+"/"+fileInfo.fileName(), this );
  if ( !pl->load() )
  {
    LogDebug() << tr( "Plugin load error! " ) << pl->errorString();
    delete pl;
  }
  else
  {
    DBCatalog_Interface *iface_DBCatalog = qobject_cast<DBCatalog_Interface *>( pl->instance() );
    QAction *action = MWidgetsCore::createMenuTree( iface_DBCatalog->categories(), m__MenuPlugins );
    connect( action, SIGNAL(triggered()), SLOT(createPluginWidget()) );
    m__Plugins << pl;
    m__PluginActivator[action] = iface_DBCatalog;
  }
  pl = NULL;
}

void Configuration_P::unloadPlugin( QPluginLoader *pl )
{
  DBCatalog_Interface *iface_DBCatalog = qobject_cast<DBCatalog_Interface *>( pl->instance() );
  MWidgetsCore::removeMenuTree(
        iface_DBCatalog->categories(), m__MenuPlugins );
  if ( !pl->unload() )
    LogDebug() << tr( "Plugin unload error! " ) << pl->errorString();
  else
  {
    m__Plugins.removeOne( pl );
    delete pl;
    pl = NULL;
  }
}

void Configuration_P::loadConfiguration()
{
  QSettings *settings = MFCCore::appSettings();

  if ( !settings->contains( KEY__PLUGIN_SOURCES ) )
    settings->setValue( KEY__PLUGIN_SOURCES, QStringList() );
  QStringList plugSources = settings->value( KEY__PLUGIN_SOURCES, QStringList() ).toStringList();

  if ( !settings->contains( KEY__PLUGIN_INSTALL ) )
    settings->setValue( KEY__PLUGIN_INSTALL, tr( "%1/plugins" ).arg( qApp->applicationDirPath() ) );
  QString plugInstall = settings->value( KEY__PLUGIN_INSTALL ).toString();
  p_dptr()->ui->lEdit_PluginsPath->setText( plugInstall );
}

void Configuration_P::saveConfiguration()
{
  QSettings *settings = MFCCore::appSettings();

  settings->setValue( KEY__PLUGIN_SOURCES, QStringList() );
  settings->setValue( KEY__PLUGIN_INSTALL, p_dptr()->ui->lEdit_PluginsPath->text() );
}

void Configuration_P::updatePlugins()
{
  QDir d( PLUGINS_PATH );
  QFileInfoList fil = d.entryInfoList( QStringList() << tr( "*.dll" ), QDir::Files, QDir::Name );
  foreach ( QFileInfo fi, fil )
  {
    QPluginLoader * pl = plugin( fi );
    if ( pl == NULL ) loadPlugin( fi );
  }
  m__MenuPlugins->menuAction()->setVisible( m__MenuPlugins->actions().count() > 0 );
}

void Configuration_P::createPluginWidget()
{
  QAction *action = qobject_cast<QAction *>( sender() );
  p_dptr()->afterPluginWidgetCreated( m__PluginActivator[action]->mainWidget() );
}

void Configuration_P::addPluginSource( const QUrl &source )
{
//  QListWidgetItem *lwi_PluginsSource = new QListWidgetItem(
//        QIcon( ":/Configuration_icons/preview.png" ), source.toString() );
//  p_dptr()->ui->listWgt_PluginSources->addItem( lwi_PluginsSource );
}
