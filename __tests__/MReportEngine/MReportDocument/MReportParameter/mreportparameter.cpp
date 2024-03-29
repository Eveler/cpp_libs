#include "mreportparameter.h"

#include "mreportparameter_p.h"
#include "mreportdocument.h"

#include <QDate>

#include <QDebug>


MReportParameter::~MReportParameter()
{
  delete p;
  p = NULL;
}

MReportDocument * MReportParameter::reportDocument() const
{
  return qobject_cast<MReportDocument *>( parent() );
}

const QString & MReportParameter::name() const
{
  return p->m__Name;
}

void MReportParameter::setParameterType( ParameterType parameterType )
{
  p->m__PT = parameterType;
}

MReportParameter::ParameterType MReportParameter::parameterType() const
{
  return p->m__PT;
}

void MReportParameter::setDataType( DataType dataType )
{
  p->m__DT = dataType;
}

MReportParameter::DataType MReportParameter::dataType() const
{
  return p->m__DT;
}

void MReportParameter::setDialogTitle( const QString &dialogTitle )
{
  if ( p->m__PT != PT_InputData ) return;

  p->m__DialogTitle = dialogTitle;
}

const QString & MReportParameter::dialogTitle() const
{
  return p->m__DialogTitle;
}

void MReportParameter::setDialogText( const QString &dialogText )
{
  if ( p->m__PT != PT_InputData ) return;

  p->m__DialogText = dialogText;
}

const QString & MReportParameter::dialogText() const
{
  return p->m__DialogText;
}

void MReportParameter::setSource( const QString &source )
{
  p->m__Source = QString();

  if ( p->m__PT == PT_SQL || p->m__PT == PT_SQLWithParameters )
  {
    foreach ( MReportSource *rs, reportDocument()->mainDocument()->reportSources() )
      if ( rs->name() == source )
      {
        p->m__Source = source;
        return;
      }
  }
  else if ( p->m__PT == PT_ForeignParameter || p->m__PT == PT_Repeater )
  {
    if ( reportDocument()->parentDocument() != NULL )
      foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
        if ( rp->name() == source )
        {
          p->m__Source = source;
          return;
        }
  }
  else if ( p->m__PT == PT_ForeignKey )
  {
    if ( reportDocument()->parentDocument() != NULL )
      foreach ( MReportKey *rk, reportDocument()->parentDocument()->reportKeys() )
        if ( rk->name() == source )
        {
          p->m__Source = source;
          return;
        }
  }
}

const QString & MReportParameter::source() const
{
  return p->m__Source;
}

void MReportParameter::setDataSource( const QString &dataSource )
{
  if ( p->m__PT != PT_SQL && p->m__PT != PT_SQLWithParameters ) return;

  p->m__DataSource = dataSource;
}

const QString & MReportParameter::dataSource() const
{
  return p->m__DataSource;
}

bool MReportParameter::setData( const QVariant &data )
{
  if ( p->m__PT != PT_InputData ) return false;
  if ( p->m__DT == DT_Date && data.type() != QVariant::Date ) return false;
  if ( p->m__DT == DT_DateList )
  {
    if ( data.type() != QVariant::List ) return false;
    else
      foreach ( QVariant value, data.toList() )
        if ( value.type() != QVariant::Date ) return false;
  }

  p->m__Data = data;
  return true;
}

QVariant MReportParameter::data() const
{
  QVariant result = p->m__Data;

  QString s = source();
  QString ds = dataSource();

  if ( p->m__PT == PT_ForeignParameter && reportDocument()->parentDocument() != NULL )
  {
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == p->m__Source ) return rp->data();
  }
  else if ( p->m__PT == PT_ForeignKey && reportDocument()->parentDocument() != NULL )
  {
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == p->m__Source ) return rp->data();
  }
  else if ( p->m__PT == PT_Repeater ) return result;
  else if ( p->m__PT == PT_SQL )
  {
//    qDebug() << __FILE__ << __LINE__ << name() << s;
//    qDebug() << __FILE__ << __LINE__ << name() << ds;
    foreach ( MReportSource *rs, reportDocument()->mainDocument()->reportSources() )
      if ( rs->name() == s )
      {
        result = rs->executeQuery( ds );
        break;
      }
//    qDebug() << __FILE__ << __LINE__ << name() << result;
  }
  else if ( p->m__PT == PT_SQLWithParameters )
  {
    QString query = ds;
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
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
        result = rs->executeQuery( query );
        break;
      }
  }

  if ( p->m__DT == DT_String )
  {
    if ( result.type() != QVariant::String )
      result = QVariant();
  }
  else if ( p->m__DT == DT_StringList )
  {
    foreach ( QVariant vd, result.toList() )
      if ( vd.type() != QVariant::String )
        result = QVariant();
  }
  else if ( p->m__DT == DT_Date )
  {
    if ( result.type() != QVariant::Date )
      result = QVariant();
  }
  else if ( p->m__DT == DT_DateList )
  {
    foreach ( QVariant vd, result.toList() )
      if ( vd.type() != QVariant::Date )
        result = QVariant();
  }

  return result;
}

void MReportParameter::setParent( QObject *parent )
{
  QObject::setParent( parent );
}

MReportParameter::MReportParameter( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportParameter_P( name, this );
}

bool MReportParameter::toFront() const
{
  if ( p->m__PT == PT_Repeater && reportDocument()->parentDocument() != NULL )
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
//    {
//      qDebug() << __FILE__ << __LINE__ << rp->name() << p->m__Source;
      if ( rp->name() == p->m__Source )
      {
        p->m__DataIterator = QListIterator<QVariant>( rp->data().toList() );
//        qDebug() << __FILE__ << __LINE__ << rp->data().toList();
        return true;
        break;
      }
//    }
  return false;
}

bool MReportParameter::hasNext() const
{
  return p->m__DataIterator.hasNext();
}

void MReportParameter::next() const
{
  p->m__Data = p->m__DataIterator.next();
}
