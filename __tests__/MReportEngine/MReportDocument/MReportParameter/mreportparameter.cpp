#include "mreportparameter.h"

#include "mreportparameter_p.h"
#include "mreportdocument.h"


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

void MReportParameter::setDataSource( const QString &dataSource )
{
  if ( p->m__PT == PT_ForeignParameter && reportDocument()->parentDocument() != NULL )
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == dataSource )
      {
        p->m__DataSource = dataSource;
        return;
      }
  else if ( p->m__PT == PT_ForeignKey && reportDocument()->parentDocument() != NULL )
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == dataSource )
      {
        p->m__DataSource = dataSource;
        return;
      }
}

const QString & MReportParameter::dataSource() const
{
  return p->m__DataSource;
}

void MReportParameter::setData( const QVariant &data )
{
  if ( p->m__PT != PT_Request ) return;
  if ( p->m__DT == DT_Date && data.type() != QVariant::Date )

  p->m__Data = data;
}

const QVariant & MReportParameter::data() const
{
  if ( p->m__PT == PT_ForeignParameter && reportDocument()->parentDocument() != NULL )
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == p->m__DataSource ) return rp->data();
  else if ( p->m__PT == PT_ForeignKey && reportDocument()->parentDocument() != NULL )
    foreach ( MReportParameter *rp, reportDocument()->parentDocument()->reportParameters() )
      if ( rp->name() == p->m__DataSource ) return rp->data();

  return p->m__Data;
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
