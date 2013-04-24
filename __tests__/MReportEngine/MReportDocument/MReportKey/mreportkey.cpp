#include "mreportkey.h"

#include "mreportkey_p.h"
#include "mreportdocument.h"
#include "mfccore.h"

#include <QDate>
#include <QStringList>

#include <QDebug>


MReportKey::~MReportKey()
{
  delete p;
  p = NULL;
}

MReportDocument *MReportKey::reportDocument() const
{
  return qobject_cast<MReportDocument *>( parent() );
}

const QString & MReportKey::name() const
{
  return p->m__Name;
}

void MReportKey::setKeyType( KeyType keyType )
{
  p->m__KT = keyType;
}

MReportKey::KeyType MReportKey::keyType() const
{
  return p->m__KT;
}

void MReportKey::setDataType( DataType dataType )
{
  p->m__DT = dataType;
}

MReportKey::DataType MReportKey::dataType() const
{
  return p->m__DT;
}

void MReportKey::setSource( const QString &source )
{
  p->m__Source = QString();

  if ( p->m__KT == KT_Parameter )
  {
    foreach ( MReportParameter *rp, reportDocument()->reportParameters() )
      if ( rp->name() == source )
      {
        p->m__Source = source;
        return;
      }
  }
  else if ( p->m__KT == KT_SQL || p->m__KT == KT_SQLWithParameters )
  {
    foreach ( MReportSource *rs, reportDocument()->mainDocument()->reportSources() )
      if ( rs->name() == source )
      {
        p->m__Source = source;
        return;
      }
  }
  else if ( p->m__KT == KT_Attachment )
  {
    if ( reportDocument()->mainDocument()->reportDocument(
           source.split( "/" ).last().split( tr( ".mrc" ) ).first() ) == NULL )
      p->m__Source = source;
  }
}

const QString & MReportKey::source() const
{
  if ( p->m__KT == KT_Attachment )
  {
    MReportDocument *attachment = reportDocument()->reportDocument(
          p->m__Source.split( "/" ).last().split( tr( ".mrc" ) ).first() );
    if ( attachment == NULL )
    {
      p->m__Source = QString();
      return p->m__Source;
    }
  }
  return p->m__Source;
}

void MReportKey::setDataSource( const QString &dataSource )
{
  if ( p->m__KT != KT_SQL && p->m__KT != KT_SQLWithParameters ) return;

  p->m__DataSource = dataSource;
}

const QString & MReportKey::dataSource() const
{
  return p->m__DataSource;
}

QString MReportKey::data() const
{
  QString result = QString();
  QVariant data = QVariant();

  QString s = source();
  QString ds = dataSource();

  if ( p->m__KT == KT_Parameter )
  {
    foreach ( MReportParameter *rp, reportDocument()->reportParameters() )
      if ( rp->name() == s ) data = rp->data();
  }
  else if ( p->m__KT == KT_SQL )
  {
    foreach ( MReportSource *rs, reportDocument()->mainDocument()->reportSources() )
      if ( rs->name() == s )
      {
        data = rs->executeQuery( ds );
        break;
      }
  }
  else if ( p->m__KT == KT_SQLWithParameters )
  {
    QString query = ds;
    foreach ( MReportParameter *rp, reportDocument()->reportParameters() )
    {
      QVariant data = rp->data();
      QString value = QString();
      if ( data.type() == QVariant::Date )
        value = data.toDate().toString( tr( "dd.MM.yyyy" ) );
      else if ( data.type() == QVariant::DateTime )
        value = data.toDateTime().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
      else if ( data.type() == QVariant::Time )
        value = data.toTime().toString( tr( "hh:mm:ss" ) );
      else if ( data.type() == QVariant::Int )
        value = QString::number( data.toInt() );
      else if ( data.type() == QVariant::UInt )
        value = QString::number( data.toUInt() );
      else if ( data.type() == QVariant::Double )
        value = QString::number( data.toDouble() );
      else if ( data.type() == QVariant::LongLong )
        value = QString::number( data.toLongLong() );
      else if ( data.type() == QVariant::ULongLong )
        value = QString::number( data.toULongLong() );
      query = query.replace( rp->name(), value );
    }
    foreach ( MReportSource *rs, reportDocument()->mainDocument()->reportSources() )
      if ( rs->name() == s )
      {
        data = rs->executeQuery( query );
        break;
      }
  }
  else if ( p->m__KT == KT_Attachment && !s.isEmpty() )
  {
    MReportDocument *attachment = reportDocument()->reportDocument(
          s.split( "/" ).last().split( tr( ".mrc" ) ).first() );
    if ( attachment != NULL ) return attachment->exec();
  }

  if ( p->m__DT == DT_Text )
  {
    if ( data.type() == QVariant::String )
      result = data.toString();
  }
  else if ( p->m__DT == DT_Date )
  {
    if ( data.type() == QVariant::Date )
      result = data.toDate().toString( tr( "dd.MM.yyyy" ) );
  }
  else if ( p->m__DT == DT_DateTime )
  {
//    qDebug() << data;
    if ( data.type() == QVariant::DateTime )
      result = data.toDateTime().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
  }
  else if ( p->m__DT == DT_Time )
  {
    if ( data.type() == QVariant::Time )
      result = data.toTime().toString( tr( "hh:mm:ss" ) );
  }
  else if ( p->m__DT == DT_Integer )
    result = QString::number( data.toInt() );
  else if ( p->m__DT == DT_Double )
    result = QString::number( data.toDouble() );
  else
  {
    if ( data.type() == QVariant::String )
      result = data.toString();
    else if ( data.type() == QVariant::Date )
      result = data.toDate().toString( tr( "dd.MM.yyyy" ) );
    else if ( data.type() == QVariant::DateTime )
      result = data.toDateTime().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
    else if ( data.type() == QVariant::Time )
      result = data.toTime().toString( tr( "hh:mm:ss" ) );
    else if ( data.type() == QVariant::Int )
      result = QString::number( data.toInt() );
    else if ( data.type() == QVariant::Double )
      result = QString::number( data.toDouble() );
  }

  return result;
}

void MReportKey::setParent( QObject *parent )
{
  QObject::setParent( parent );
}

MReportKey::MReportKey( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportKey_P( name, this );
}
