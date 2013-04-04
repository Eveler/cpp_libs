#include "pluginssourceloader_p.h"

#include "widget_pluginssourceloader.h"
#include "ui_widget_pluginssourceloader.h"

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
  m__FullUpdate(false)
{
  currentUpdate.first = NULL;
  currentUpdate.second = QByteArray();
  m__NetworkAM = new QNetworkAccessManager( this );
  connect( m__NetworkAM, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)) );
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

bool PluginsSourceLoader_P::addPluginSource( const QUrl &source )
{
  if ( !source.isValid() || source.scheme().isEmpty() ) return false;

  if ( !p_dptr()->ui->progressBar->isVisible() )
    p_dptr()->ui->progressBar->setVisible( true );

  QListWidgetItem *lwi_PluginsSource = new QListWidgetItem(
        QIcon( ":/PluginsSourceLoader_icons/preview_disabled.png" ), source.toString() );
  p_dptr()->ui->listWgt_PluginSources->addItem( lwi_PluginsSource );
  p_dptr()->ui->listWgt_PluginSources->setCurrentItem( lwi_PluginsSource );
  qApp->processEvents();

  updatePluginSource( lwi_PluginsSource );

  return true;
}

void PluginsSourceLoader_P::updatePluginSource( QListWidgetItem *pluginSource )
{
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

  QDomElement element = doc.documentElement();
  for( QDomNode fileNode = element.firstChild();
       !fileNode.isNull(); fileNode = fileNode.nextSibling() )
    for( QDomNode fileAttr = fileNode.toElement().firstChild();
         !fileAttr.isNull(); fileAttr = fileAttr.nextSibling() )
      LogDebug() << fileAttr.toElement().text();
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
    p_dptr()->ui->progressBar->setVisible( false );
  }
}

void PluginsSourceLoader_P::replyFinished( QNetworkReply *reply )
{
  reply->deleteLater();

  parseXML( currentUpdate.second );

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
