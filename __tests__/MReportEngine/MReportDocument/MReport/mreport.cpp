#include "mreport.h"

#include "mreportdocument.h"
#include "quazipfile.h"
#include "quazipdir.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDomDocument>
#include <QStringList>

#include <QDebug>


MReportDocument * MReport::load( const QString &filePath, QString *errorStr, QObject *parent )
{
  QFileInfo fi( filePath );
  if ( fi.suffix() != QObject::tr( "mrf" ) )
  {
    *errorStr = QObject::tr( "Неверный формат файла отчета!" );
    return NULL;
  }
  if ( !fi.exists() )
  {
    *errorStr = QObject::tr( "Файл отчета не найден!" );
    return NULL;
  }

  QDir workDir( fi.absolutePath() );
  if ( workDir.exists( fi.baseName() ) )
  {
    *errorStr = QObject::tr( "Файл отчета уже используется!" );
    return NULL;
  }
  workDir.mkdir( fi.baseName() );
  QDir dir = QDir( QObject::tr( "%1/%2" ).arg( fi.absolutePath(), fi.baseName() ) );

  QuaZip zipF( filePath );
  if ( !zipF.open( QuaZip::mdUnzip ) )
  {
    *errorStr = QObject::tr( "Zip error №%1" ).arg( zipF.getZipError() );
    return NULL;
  }

  QuaZipFile zObject( &zipF );
  for( bool more = zipF.goToFirstFile(); more; more = zipF.goToNextFile() )
  {
    QuaZipFileInfo zFI;
    zObject.getFileInfo( &zFI );
    QString name = zFI.name;
    if ( zFI.name.right( 1 ) == QString( "/" ) )
    {
      name = name.remove( name.length()-1, 1 );
      dir.mkpath( QObject::tr( "%1/%2" ).arg( dir.absolutePath(), name ) );
    }
    else
    {
      QFile f( QObject::tr( "%1/%2" ).arg( dir.absolutePath(), name ) );
      if ( f.exists() )
      {
        if ( !f.remove() ) continue;
      }

      zObject.open( QIODevice::ReadOnly );
      if ( f.open( QFile::WriteOnly ) )
        f.write( zObject.readAll() );
      f.close();
      zObject.close();
    }
  }


  MReportDocument *reportDocument = new MReportDocument(
        QObject::tr( "%1/%2.mrc" ).arg( dir.absolutePath(), dir.dirName() ), parent );
  load( reportDocument );

  QListIterator<QuaZipFileInfo> iZFI = QListIterator<QuaZipFileInfo>( zipF.getFileInfoList() );
  iZFI.toBack();
  while ( iZFI.hasPrevious() )
  {
    QuaZipFileInfo zFI = iZFI.previous();
    QString name = zFI.name;
    if ( name.right( 1 ) == QString( "/" ) )
    {
      name = name.remove( name.length()-1, 1 );
      QDir( QObject::tr( "%1/%2" ).arg( workDir.absolutePath(), dir.dirName() ) ).rmpath( name );
    }
    else QFile( QObject::tr( "%1/%2/%3" ).arg( workDir.absolutePath(), dir.dirName(), name ) ).remove();
  }
  workDir.rmdir( dir.dirName() );

  zipF.close();

  return reportDocument;
}

MReportDocument * MReport::create( const QString &alias, const QString &dirPath, QObject *parent )
{
  QDir d ( dirPath );

  if ( !d.exists() && !d.mkpath( d.absolutePath() ) ) d = QDir( "./" );

  if ( !d.exists( alias ) ) d.mkdir( alias );

  QString cfgFile = QObject::tr( "%1/%2/%2.mrc" ).arg( d.absolutePath(), alias );
  QString htmlFile = QObject::tr( "%1/%2/main.html" ).arg( d.absolutePath(), alias );

  if ( QFile::exists( cfgFile ) || QFile::exists( htmlFile ) ) return NULL;

  QDomDocument document;
  document.appendChild( document.createElement( QObject::tr( "report" ) ) );

  QFile fCfg( cfgFile );
  QFile fHtml( htmlFile );
  if ( fCfg.open( QFile::WriteOnly | QFile::Text ) )
  {
    if ( !fHtml.open( QFile::WriteOnly | QFile::Text ) )
    {
      fCfg.close();
      fCfg.remove();
      return NULL;
    }
    fHtml.close();
    fCfg.write( document.toString().toLocal8Bit() );
  }
  else return NULL;
  fCfg.close();

  return new MReportDocument( cfgFile, parent );
}

bool MReport::save( MReportDocument *reportDocument )
{
  return true;
}

void MReport::load( MReportDocument *reportDocument )
{
  QFileInfo fi( reportDocument->fileName() );

  QFile f( QObject::tr( "%1/main.html" ).arg( fi.absolutePath() ) );
  f.open( QFile::ReadOnly | QFile::Text );
  reportDocument->setBody( f.readAll() );
  f.close();

  f.setFileName( reportDocument->fileName() );
  f.open( QFile::ReadOnly | QFile::Text );
  reportDocument->setLastError( parse( f.readAll(), reportDocument ) );
  f.close();
}

void MReport::addError( const QString &error, QStringList &errors )
{
  if ( error.isEmpty() ) return;
  errors << error;
}

QString MReport::parse( const QByteArray &data, MReportDocument *reportDocument )
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

QString MReport::sources( const QDomNode &tag, MReportDocument *reportDocument )
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

QString MReport::parameters( const QDomNode &tag, MReportDocument *reportDocument )
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

QString MReport::keys( const QDomNode &tag, MReportDocument *reportDocument )
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
      load( reportDocument->addReportDocument( keySource, rk ) );
  }

  return result.join( "\n" );
}
