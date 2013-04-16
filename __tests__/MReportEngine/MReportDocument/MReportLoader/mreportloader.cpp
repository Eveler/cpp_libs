#include "mreportloader.h"

#include "mreportdocument.h"

#include <QFile>
#include <QDomDocument>

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

QString MReportLoader::parse( const QByteArray &data, MReportDocument *reportDocument )
{
  QDomDocument document;
  QString err_text = QString();
  int err_line = 0;
  int err_column = 0;
  if ( !document.setContent( data, &err_text, &err_line, &err_column ) )
    return QObject::tr( "%1\nстрока: %2\nпозиция: %3" ).arg(
          err_text ).arg( err_line ).arg( err_column );

  QDomElement mainElement = document.documentElement();
  err_text = parameters( mainElement.namedItem( QObject::tr( "parameters" ) ), reportDocument );

  return err_text;
}

QString MReportLoader::parameters( const QDomNode &tagParameters, MReportDocument *reportDocument )
{
  QString result = QString();

  if ( tagParameters.isNull() ) return result;
  if ( tagParameters.childNodes().isEmpty() )
    return QObject::tr( "тэг parameters пуст" );

  for ( QDomNode tagParameter = tagParameters.firstChild();
        !tagParameter.isNull(); tagParameter = tagParameter.nextSibling() )
  {
    QString parameterName = tagParameter.toElement().attribute( QObject::tr( "name" ) );
    if ( parameterName.isEmpty() || parameterName.contains( " " ) )
    {
      result += ( !result.isEmpty() ? "\n" : "" )+
          QObject::tr( "имя параметра имеет неверный формат" );
      continue;
    }
    MReportParameter *rp = reportDocument->addReportParameter( parameterName );
    if ( rp == NULL )
    {
      result += ( !result.isEmpty() ? "\n" : "" )+
          QObject::tr( "параметр с именем %1 уже существует" ).arg( parameterName );
      continue;
    }
    QString parameterType = tagParameter.namedItem(
          QObject::tr( "parameter_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString parameterDataType = tagParameter.namedItem(
          QObject::tr( "parameter_data_type" ) ).toElement().attribute( QObject::tr( "name" ) );
    QString parameterDataSource = tagParameter.namedItem(
          QObject::tr( "parameter_data_source" ) ).toElement().attribute( QObject::tr( "value" ) );
    if ( parameterType == QObject::tr( "InputData" ) )
    {
      rp->setParameterType( MReportParameter::PT_InputData );
      if ( parameterDataType == QObject::tr( "DatePeriod" ) )
        rp->setDataType( MReportParameter::DT_DatePeriod );
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
      result += ( !result.isEmpty() ? "\n" : "" )+
          QObject::tr( "параметр с именем %1 имеет неверный формат" ).arg( parameterName );
  }

  return QString();
}
