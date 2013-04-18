#include "mreportloader.h"

#include "mreportdocument.h"

#include <QFile>
#include <QDomDocument>
#include <QStringList>

//#include <QDebug>


QString MReportLoader::load( MReportDocument *reportDocument )
{
  QFile f( reportDocument->fileName() );
//  qDebug() << f.fileName();
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
    return QObject::tr( "%1 [строка: %2 позиция: %3]" ).arg(
          err_text ).arg( err_line ).arg( err_column );
  addError( err_text, result );

  QDomElement mainElement = document.documentElement();
  addError( parameters( mainElement.namedItem( QObject::tr( "parameters" ) ), reportDocument ), result );
  addError( keys( mainElement.namedItem( QObject::tr( "keys" ) ), reportDocument ), result );

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
      addError( QObject::tr( "имя параметра имеет неверный формат" ), result );
      continue;
    }
    MReportParameter *rp = reportDocument->addReportParameter( parameterName );
    if ( rp == NULL )
    {
      addError( QObject::tr( "параметр с именем %1 уже существует" ).arg( parameterName ), result );
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
      addError( QObject::tr( "параметр с именем %1 имеет неверный формат" ).arg(
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
      addError( QObject::tr( "имя ключа имеет неверный формат" ), result );
      continue;
    }
    MReportKey *rk = reportDocument->addReportKey( keyName );
    if ( rk == NULL )
    {
      addError( QObject::tr( "ключ с именем %1 уже существует" ).arg( keyName ), result );
      continue;
    }
    QString keyType = tagKey.namedItem(
          QObject::tr( "key_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString keyDataType = tagKey.namedItem(
          QObject::tr( "key_data_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString keyDataSource = tagKey.namedItem(
          QObject::tr( "key_data_source" ) ).toElement().attribute( QObject::tr( "value" ) );
    if ( keyType == QObject::tr( "InputData" ) )
    {
      rk->setKeyType( MReportParameter::PT_InputData );
      if ( keyDataType == QObject::tr( "DatePeriod" ) )
        rk->setDataType( MReportParameter::DT_DatePeriod );
    }
    else if ( keyType == QObject::tr( "Repeater" ) )
    {
      rk->setKeyType( MReportParameter::PT_Repeater );
      rk->setDataSource( keyDataSource );
    }
    else if ( keyType == QObject::tr( "Foreign parameter" ) )
    {
      rk->setKeyType( MReportParameter::PT_ForeignParameter );
      rk->setDataSource( keyDataSource );
    }
    else if ( keyType == QObject::tr( "Foreign key" ) )
    {
      rk->setKeyType( MReportParameter::PT_ForeignKey );
      rk->setDataSource( keyDataSource );
    }
    else
      addError( QObject::tr( "ключ с именем %1 имеет неверный формат" ).arg(
                  keyName ), result );
  }

  return result.join( "\n" );
}
