#include "mreportkey.h"

#include "mreportkey_p.h"
#include "mreportdocument.h"

#include <QDate>
#include <QStringList>


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

void MReportKey::setDataSource( const QString &dataSource )
{
  p->m__DataSource = QString();

  if ( p->m__KT == KT_Parameter )
  {
    foreach ( MReportParameter *rp, reportDocument()->reportParameters() )
      if ( rp->name() == dataSource )
      {
        p->m__DataSource = dataSource;
        return;
      }
  }
  else if ( p->m__KT == KT_SQL || p->m__KT == KT_SQLWithParameters )
    p->m__DataSource = dataSource;
  else if ( p->m__KT == KT_Attachment )
  {
    if ( reportDocument()->mainDocument()->reportDocument(
           dataSource.split( "/" ).last().split( tr( ".mrc" ) ).first() ) == NULL )
      p->m__DataSource = dataSource;
  }
}

const QString & MReportKey::dataSource() const
{
  if ( p->m__KT == KT_Attachment )
  {
    MReportDocument *attachment = reportDocument()->reportDocument(
          p->m__DataSource.split( "/" ).last().split( tr( ".mrc" ) ).first() );
    if ( attachment == NULL )
    {
      p->m__DataSource = QString();
      return p->m__DataSource;
    }
  }
  return p->m__DataSource;
}

QString MReportKey::data() const
{
  QString result = QString();
  QVariant data = QVariant();

  QString ds = dataSource();

  if ( p->m__KT == KT_Parameter )
  {
    foreach ( MReportParameter *rp, reportDocument()->reportParameters() )
      if ( rp->name() == ds ) data = rp->data();
  }
  else if ( p->m__KT == KT_SQL )
    data = reportDocument()->mainDocument()->sqlResult( ds );
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
        value = data.toDate().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
      else if ( data.type() == QVariant::Time )
        value = data.toDate().toString( tr( "hh:mm:ss" ) );
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
    data = reportDocument()->mainDocument()->sqlResult( query );
  }
  else if ( p->m__KT == KT_Attachment && !ds.isEmpty() )
  {
    MReportDocument *attachment = reportDocument()->reportDocument(
          ds.split( "/" ).last().split( tr( ".mrc" ) ).first() );
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
    if ( data.type() == QVariant::DateTime )
      result = data.toDate().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
  }
  else if ( p->m__DT == DT_Time )
  {
    if ( data.type() == QVariant::Time )
      result = data.toDate().toString( tr( "hh:mm:ss" ) );
  }
  else if ( p->m__DT == DT_Integer )
    result = QString::number( data.toInt() );
  else if ( p->m__DT == DT_Double )
    result = QString::number( data.toDouble() );

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
