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

void Widget_PluginsSourceLoader::setPluginsSources( const QStringList &sources )
{
  p->m__PluginPaths.clear();
  foreach ( QString source, sources ) p->addPluginSource( QUrl( source ) );
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
  do
  {
    sourceInput->setTextValue( source.toString() );
    res = sourceInput->exec();
    source.setUrl( sourceInput->textValue() );
  } while ( res == (int)QDialog::Accepted && !p->addPluginSource( source ) );
  delete sourceInput;
  sourceInput = NULL;
}
