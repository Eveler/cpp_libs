#include "widget_pluginssourceloader.h"
#include "ui_widget_pluginssourceloader.h"

#include "pluginssourceloader_p.h"
#include "dialog_newplugins.h"

#include <QInputDialog>
#include <QUrl>
#include <QDir>


Widget_PluginsSourceLoader::Widget_PluginsSourceLoader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_PluginsSourceLoader)
{
  ui->setupUi(this);

  p = new PluginsSourceLoader_P( this );

  ui->tabWidget->setCurrentWidget( ui->tab_SourceList );
}

Widget_PluginsSourceLoader::~Widget_PluginsSourceLoader()
{
  delete ui;
  ui = NULL;
}

void Widget_PluginsSourceLoader::setPluginsSourceList( const QStringList &sourceList )
{
  foreach ( QString source, sourceList ) p->addPluginSource( QUrl( source ) );
}

QStringList Widget_PluginsSourceLoader::pluginsSourceList() const
{
  QStringList result = QStringList();
  for ( int index = 0; index < ui->listWgt_PluginSources->count(); index++ )
    result << ui->listWgt_PluginSources->item( index )->text();
  return result;
}

void Widget_PluginsSourceLoader::setInstallPath( const QString &installPath )
{
  QString path = installPath.simplified();
  QDir dir( path );
  if ( ( !dir.exists() && !dir.mkpath( path ) ) || path.isEmpty() )
    path = qApp->applicationDirPath();

  ui->lEdit_InstallPath->setText( path );
}

const QString & Widget_PluginsSourceLoader::installPath() const
{
  return ui->lEdit_InstallPath->text();
}

const QStringList & Widget_PluginsSourceLoader::plugins() const
{
  return p->m__PluginPaths;
}

const QByteArray & Widget_PluginsSourceLoader::pluginHash( const QString &plugin ) const
{
  if ( p->m__PluginHash.contains( plugin ) )
    return p->m__PluginHash[plugin];
  return p->nullHash;
}

void Widget_PluginsSourceLoader::on_tBt_AddSource_clicked()
{
  QInputDialog *sourceInput = new QInputDialog( this );
  sourceInput->setFixedSize( 500, 190 );
  sourceInput->setInputMode( QInputDialog::TextInput );
  sourceInput->setWindowTitle( tr( "Новый источник инструментария" ) );
  sourceInput->setLabelText( tr( "Введите URL источника инструментария" ) );
  sourceInput->setOkButtonText( tr( "Ок" ) );
  sourceInput->setCancelButtonText( tr( "Отмена" ) );
  QUrl source = QUrl();
  int res = (int)QDialog::Accepted;
  bool repeat = false;
  do
  {
    sourceInput->setTextValue( source.toString() );
    res = sourceInput->exec();
    source.setUrl( sourceInput->textValue() );
    repeat = false;
    if ( res == (int)QDialog::Accepted )
    {
      QListWidgetItem *lwi = p->addPluginSource( source );
      if ( lwi == NULL ) repeat = true;
      else ui->listWgt_PluginSources->setCurrentItem( lwi );
      if ( !repeat ) emit pluginsSourceListChanged();
    }
  } while ( repeat );
  delete sourceInput;
  sourceInput = NULL;
}

void Widget_PluginsSourceLoader::on_tabWidget_currentChanged( int index )
{
  if ( index == ui->tabWidget->indexOf( ui->tab_PluginList ) &&
       !p->m__DialogNewPlugins->pluginNames().isEmpty() )
    p->m__DialogNewPlugins->exec();
}
