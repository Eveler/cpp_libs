#include "widget_pluginssourceloader.h"
#include "ui_widget_pluginssourceloader.h"

#include "pluginssourceloader_p.h"

#include <QInputDialog>
#include <QUrl>


Widget_PluginsSourceLoader::Widget_PluginsSourceLoader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_PluginsSourceLoader)
{
  ui->setupUi(this);

  p = new PluginsSourceLoader_P( this );
}

Widget_PluginsSourceLoader::~Widget_PluginsSourceLoader()
{
  delete ui;
  ui = NULL;
}

void Widget_PluginsSourceLoader::setPluginsSourceList( const QStringList &sourceList )
{
  ui->listWgt_PluginSources->clear();
  p->m__PluginPaths.clear();
  p->m__FullUpdate = true;
  foreach ( QString source, sourceList ) p->addPluginSource( QUrl( source ) );
}

QStringList Widget_PluginsSourceLoader::pluginsSourceList() const
{
  QStringList result = QStringList();
  for ( int index = 0; index < ui->listWgt_PluginSources->count(); index++ )
    result << ui->listWgt_PluginSources->item( index )->text();
  return result;
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
    }
  } while ( repeat );
  delete sourceInput;
  sourceInput = NULL;
}
