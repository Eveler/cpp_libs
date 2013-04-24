#include "mreportloader.h"

#include "mreportdocument.h"

#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QStringList>

#include <QDebug>


QString MReportLoader::load( MReportDocument *reportDocument )
{
  QFile f( reportDocument->fileName() );
  if ( !f.open( QFile::ReadOnly | QFile::Text ) )
    return QObject::tr( "невозможно открыть файл конфигурации '%1'" ).arg( reportDocument->fileName() );

  QString err_text = parse( f.readAll(), reportDocument );
  f.close();

  return err_text;
}

void MReportLoader::addError( const QString &error, QStringList &errors )
{
  if ( error.isEmpty() ) return;
  errors << error;
}

QString MReportLoader::parse( const QByteArray &data, MReportDocument *reportDocument )
{
  QStringList result = QStringList();

  QDomDocument document;
  QString err_text = QString();
  int err_line = 0;
  int err_column = 0;
  if ( !document.setContent( data, &err_text, &err_line, &err_column ) )
    err_text = QObject::tr( "%1 [строка: %2 позиция: %3]" ).arg(
          err_text ).arg( err_line ).arg( err_column );
  addError( err_text, result );

  QDomElement mainElement = document.documentElement();
  addError( sources( mainElement.namedItem( QObject::tr( "sources" ) ), reportDocument ), result );
  addError( parameters( mainElement.namedItem( QObject::tr( "parameters" ) ), reportDocument ), result );
  addError( keys( mainElement.namedItem( QObject::tr( "keys" ) ), reportDocument ), result );

  if ( !result.isEmpty() )
    result.prepend( QObject::tr( "%1 ошибок в файле %2" ).arg(
                      result.count() ).arg( reportDocument->fileName() ) );

  return result.join( "\n" );
}

QString MReportLoader::sources( const QDomNode &tag, MReportDocument *reportDocument )
{
  QStringList result = QStringList();

  if ( tag.isNull() ) return QString();
  if ( tag.childNodes().isEmpty() )
    return QObject::tr( "тэг keys пуст" );

  for ( QDomNode tagSource = tag.firstChild();
        !tagSource.isNull(); tagSource = tagSource.nextSibling() )
  {
    QString sourceName = tagSource.toElement().attribute( QObject::tr( "name" ) );
    if ( sourceName.isEmpty() || sourceName.contains( " " ) )
    {
      addError( QObject::tr( "имя источника '%1' имеет неверный формат" ).arg( sourceName ), result );
      continue;
    }
    MReportSource *rs = reportDocument->addReportSource( sourceName );
    if ( rs == NULL )
    {
      addError( QObject::tr( "источник %1 уже существует" ).arg( sourceName ), result );
      continue;
    }
    QString sourceType = tagSource.namedItem(
          QObject::tr( "source_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QDomElement elemParams = tagSource.namedItem( QObject::tr( "source_params" ) ).toElement();
    QString driver = elemParams.attribute( QObject::tr( "driver" ) );
    QString host = elemParams.attribute( QObject::tr( "host" ) );
    QString port = elemParams.attribute( QObject::tr( "port" ) );
    QString database = elemParams.attribute( QObject::tr( "database" ) );

    if ( sourceType == QObject::tr( "SQL" ) ) rs->setSourceType( MReportSource::ST_SQL );
    rs->setDriverName( driver );
    rs->setHost( host );
    rs->setPort( port.toInt() );
    rs->setDatabaseName( database );
  }

  return result.join( "\n" );
}

QString MReportLoader::parameters( const QDomNode &tag, MReportDocument *reportDocument )
{
  QStringList result = QStringList();

  if ( tag.isNull() ) return QString();
  if ( tag.childNodes().isEmpty() )
    return QObject::tr( "тэг parameters пуст" );

  for ( QDomNode tagKey = tag.firstChild();
        !tagKey.isNull(); tagKey = tagKey.nextSibling() )
  {
    QString parameterName = tagKey.toElement().attribute( QObject::tr( "name" ) );
    if ( parameterName.isEmpty() || parameterName.contains( " " ) )
    {
      addError( QObject::tr( "имя параметра '%1' имеет неверный формат" ).arg( parameterName ), result );
      continue;
    }
    MReportParameter *rp = reportDocument->addReportParameter( parameterName );
    if ( rp == NULL )
    {
      addError( QObject::tr( "параметр %1 уже существует" ).arg( parameterName ), result );
      continue;
    }
    QString parameterType = tagKey.namedItem(
          QObject::tr( "parameter_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString parameterDataType = tagKey.namedItem(
          QObject::tr( "parameter_data_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString parameterDataSource = tagKey.namedItem(
          QObject::tr( "parameter_data_source" ) ).toElement().attribute( QObject::tr( "value" ) );
    if ( parameterType == QObject::tr( "InputData" ) )
    {
      rp->setParameterType( MReportParameter::PT_InputData );
      if ( parameterDataType == QObject::tr( "DatePeriod" ) )
        rp->setDataType( MReportParameter::DT_DatePeriod );
    }
    else if ( parameterType == QObject::tr( "Repeater" ) )
    {
      rp->setParameterType( MReportParameter::PT_Repeater );
      rp->setDataSource( parameterDataSource );
    }
    else if ( parameterType == QObject::tr( "Foreign parameter" ) )
    {
      rp->setParameterType( MReportParameter::PT_ForeignParameter );
      rp->setDataSource( parameterDataSource );
    }
    else if ( parameterType == QObject::tr( "Foreign key" ) )
    {
      rp->setParameterType( MReportParameter::PT_ForeignKey );
      rp->setDataSource( parameterDataSource );
    }
    else
      addError( QObject::tr( "параметр '%1' имеет неверный формат" ).arg(
                  parameterName ), result );
  }

  return result.join( "\n" );
}

QString MReportLoader::keys( const QDomNode &tag, MReportDocument *reportDocument )
{
  QStringList result = QStringList();

  if ( tag.isNull() ) return QString();
  if ( tag.childNodes().isEmpty() )
    return QObject::tr( "тэг keys пуст" );

  for ( QDomNode tagKey = tag.firstChild();
        !tagKey.isNull(); tagKey = tagKey.nextSibling() )
  {
    QString keyName = tagKey.toElement().attribute( QObject::tr( "name" ) );
    if ( keyName.isEmpty() || keyName.contains( " " ) )
    {
      addError( QObject::tr( "имя ключа '%1' имеет неверный формат" ).arg( keyName ), result );
      continue;
    }
    MReportKey *rk = reportDocument->addReportKey( keyName );
    if ( rk == NULL )
    {
      addError( QObject::tr( "ключ '%1' уже существует" ).arg( keyName ), result );
      continue;
    }
    QString keySourceType = tagKey.namedItem(
          QObject::tr( "key_source_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString keySource = tagKey.namedItem(
          QObject::tr( "key_source" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString keyDataType = tagKey.namedItem(
          QObject::tr( "key_data_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString keyDataSource = tagKey.namedItem(
          QObject::tr( "key_data_source" ) ).toElement().attribute( QObject::tr( "value" ) );

    MReportKey::KeyType kt = MReportKey::KT_Undefined;
    MReportKey::DataType dt = MReportKey::DT_Undefined;

    if ( keySourceType == QObject::tr( "Parameter" ) ) kt
        = MReportKey::KT_Parameter;
    else if ( keySourceType == QObject::tr( "SQL" ) )
      kt = MReportKey::KT_SQL;
    else if ( keySourceType == QObject::tr( "SQL with parameters" ) )
      kt = MReportKey::KT_SQLWithParameters;
    else if ( keySourceType == QObject::tr( "Attachment" ) )
      kt = MReportKey::KT_Attachment;
    else
      addError( QObject::tr( "ключ '%1' имеет неверный тип [%2]" ).arg(
                  keyName, keySourceType ), result );

    if ( keyDataType == QObject::tr( "Text" ) ) dt = MReportKey::DT_Text;
    else if ( keyDataType == QObject::tr( "Date" ) ) dt = MReportKey::DT_Date;
    else if ( keyDataType == QObject::tr( "DateTime" ) ) dt = MReportKey::DT_DateTime;
    else if ( keyDataType == QObject::tr( "Time" ) ) dt = MReportKey::DT_Time;
    else if ( keyDataType == QObject::tr( "Integer" ) ) dt = MReportKey::DT_Integer;
    else if ( keyDataType == QObject::tr( "Double" ) ) dt = MReportKey::DT_Double;
    else if ( kt != MReportKey::KT_Parameter && kt != MReportKey::KT_Attachment )
      addError( QObject::tr( "ключ '%1'::%2 имеет неверный тип данных [%3]" ).arg(
                  keyName, keySourceType, keyDataType ), result );

    rk->setKeyType( kt );
    rk->setSource( keySource );
    rk->setDataType( dt );
    rk->setDataSource( keyDataSource );

    if ( kt == MReportKey::KT_Attachment )
      reportDocument->addReportDocument( keySource, rk );
  }

  return result.join( "\n" );
}
