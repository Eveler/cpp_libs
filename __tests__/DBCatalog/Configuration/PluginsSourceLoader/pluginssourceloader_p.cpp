#include "pluginssourceloader_p.h"

#include "widget_pluginssourceloader.h"
#include "ui_widget_pluginssourceloader.h"
#include "dialog_newplugins.h"
#include "mfccore.h"

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QDomDocument>

#include "amslogger.h"


PluginsSourceLoader_P::PluginsSourceLoader_P( Widget_PluginsSourceLoader *parent ) :
  QObject(parent),
  m__PluginPaths(QStringList()),
  m__PluginHash(QHash<QString, QByteArray>()),
  nullHash(QByteArray()),
  isNewSource(false),
  m__FullUpdate(false)
{
  currentUpdate.first = NULL;
  currentUpdate.second = QByteArray();
  m__NetworkAM = new QNetworkAccessManager( this );
  connect( m__NetworkAM, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)) );
  parent->ui->progressBar->setVisible( false );
  m__DialogNewPlugins = new Dialog_NewPlugins( p_dptr() );
  m__DialogNewPlugins->setFixedSize( 350, 450 );
  m__DialogNewPlugins->setWindowTitle( tr( "Новый инструментарий" ) );
  connect( m__DialogNewPlugins, SIGNAL(accepted()), SLOT(newPluginsSelected()) );
}

PluginsSourceLoader_P::~PluginsSourceLoader_P()
{
  delete m__NetworkAM;
  m__NetworkAM = NULL;

  currentUpdate.first = NULL;
  currentUpdate.second.clear();
}

Widget_PluginsSourceLoader * PluginsSourceLoader_P::p_dptr() const
{
  return qobject_cast<Widget_PluginsSourceLoader *>( parent() );
}

QListWidgetItem * PluginsSourceLoader_P::addPluginSource( const QUrl &source, bool newPluginsNotify )
{
  if ( !source.isValid() || source.scheme().isEmpty() ||
       !p_dptr()->ui->listWgt_PluginSources->findItems(
         source.toString(), Qt::MatchFixedString ).isEmpty() ) return NULL;

  QListWidgetItem *lwi_PluginsSource = new QListWidgetItem(
        QIcon( ":/PluginsSourceLoader_icons/preview_disabled.png" ), source.toString() );
  p_dptr()->ui->listWgt_PluginSources->addItem( lwi_PluginsSource );

  if ( newPluginsNotify ) isNewSource = true;

  if ( !p_dptr()->ui->progressBar->isVisible() )
    p_dptr()->ui->progressBar->setVisible( true );

  updatePluginSource( lwi_PluginsSource );

  return lwi_PluginsSource;
}

void PluginsSourceLoader_P::updatePluginSource( QListWidgetItem *pluginSource )
{
  p_dptr()->ui->tBt_CheckUpdate->setDisabled( true );
  p_dptr()->ui->tabWidget->setTabEnabled(
        p_dptr()->ui->tabWidget->indexOf( p_dptr()->ui->tab_PluginList ), false );
  p_dptr()->ui->tBt_AddSource->setDisabled( true );
  p_dptr()->ui->tBt_RemoveSource->setDisabled( true );

  currentUpdate.first = pluginSource;
  p_dptr()->ui->progressBar->setRange( 0, 0 );

  QNetworkReply *reply = m__NetworkAM->get(
        QNetworkRequest( QUrl( tr( "%1/file_list.xml" ).arg( currentUpdate.first->text() ) ) ) );
  connect( reply, SIGNAL(readyRead()), SLOT(readyReadData()) );
  connect( reply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)) );
  connect( reply, SIGNAL(error(QNetworkReply::NetworkError)),
           SLOT(downloadError(QNetworkReply::NetworkError)) );
}

void PluginsSourceLoader_P::parseXML( const QByteArray &xml )
{
  QDomDocument doc;
  doc.setContent( xml );

  for( QDomNode fileNode = doc.documentElement().firstChild();
       !fileNode.isNull(); fileNode = fileNode.nextSibling() )
  {
    QString plugPath = fileNode.namedItem(
          tr( "path" ) ).toElement().attribute( tr( "value" ) ).replace( "\\", "/" );
    QString plugName = plugPath.split( "/" ).last();
    QString plugHash = fileNode.namedItem( tr( "hash" ) ).toElement().attribute( tr( "value" ) );
    QAbstractItemModel *absMdl = p_dptr()->ui->tableWidget->model();
    if ( MFCCore::findIndexes( absMdl, plugName ).isEmpty() )
    {
      m__PluginPaths << plugPath;
      m__PluginHash[plugPath] = plugHash.toLocal8Bit();
      absMdl->insertRow( absMdl->rowCount() );
      absMdl->setData( absMdl->index( absMdl->rowCount()-1, 0 ), plugName );
      absMdl->setData( absMdl->index( absMdl->rowCount()-1, 1 ), tr( "Новый" ) );
      if ( isNewSource )
        m__DialogNewPlugins->addPluginName( plugName );
    }
  }
  if ( isNewSource ) isNewSource = false;
}

void PluginsSourceLoader_P::nextPluginSource()
{
  if ( currentUpdate.first == NULL ) return;
  currentUpdate.second.clear();
  int index = p_dptr()->ui->listWgt_PluginSources->row( currentUpdate.first );
  if ( index+1 < p_dptr()->ui->listWgt_PluginSources->count() && m__FullUpdate )
    updatePluginSource( p_dptr()->ui->listWgt_PluginSources->item( index+1 ) );
  else
  {
    currentUpdate.first = NULL;
    m__FullUpdate = false;
    p_dptr()->ui->progressBar->setVisible( false );
  }
}

void PluginsSourceLoader_P::replyFinished( QNetworkReply *reply )
{
  reply->deleteLater();
  reply = NULL;

  parseXML( currentUpdate.second );

  p_dptr()->ui->tBt_CheckUpdate->setEnabled( true );
  p_dptr()->ui->tabWidget->setTabEnabled(
        p_dptr()->ui->tabWidget->indexOf( p_dptr()->ui->tab_PluginList ), true );
  p_dptr()->ui->tBt_AddSource->setEnabled( true );
  p_dptr()->ui->tBt_RemoveSource->setEnabled( true );

  nextPluginSource();
}

void PluginsSourceLoader_P::readyReadData()
{
  if ( currentUpdate.first == NULL ) return;
  QNetworkReply *reply = qobject_cast<QNetworkReply *>( sender() );
  currentUpdate.second.append( reply->readAll() );
}

void PluginsSourceLoader_P::downloadProgress( qint64 current, qint64 overall )
{
  if ( currentUpdate.first == NULL ) return;

  if ( p_dptr()->ui->progressBar->maximum() == 0 )
  {
    p_dptr()->ui->progressBar->setRange( 0, 1000 );
    currentUpdate.first->setIcon( QIcon( ":/PluginsSourceLoader_icons/preview.png" ) );
  }
  p_dptr()->ui->progressBar->setValue( (int)((double)current/(double)overall*1000.) );
}

void PluginsSourceLoader_P::downloadError( QNetworkReply::NetworkError )
{
  currentUpdate.first->setIcon( QIcon( ":/PluginsSourceLoader_icons/preview_disabled.png" ) );
  nextPluginSource();
}

void PluginsSourceLoader_P::newPluginsSelected()
{
  m__DialogNewPlugins->clear();
}
