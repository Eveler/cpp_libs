#include "mfcdocumentinfo.h"

#include <QMetaProperty>

#include "amslogger.h"


QList<MFCDocumentInfo *> MFCDocumentInfo::instances = QList<MFCDocumentInfo *>();

MFCDocumentInfo * MFCDocumentInfo::instance(
    QString doc_type, QString doc_name, QString doc_series,
    QString doc_number, QDate doc_date, QDate doc_expires,
    QString doc_agency, QDateTime doc_createdate, QObject *parent )
{
  foreach ( MFCDocumentInfo *docInfo, instances )
  {
    if( docInfo->type() == doc_type && docInfo->date() == doc_date &&
        docInfo->createDate() == doc_createdate && docInfo->number() == doc_number &&
        docInfo->name() == doc_name && docInfo->series() == doc_series &&
        docInfo->expiresDate() == doc_expires && docInfo->agency() == doc_agency )
      return docInfo;
  }

  MFCDocumentInfo *docI=new MFCDocumentInfo( parent );
  docI->setType( doc_type );
  docI->setName( doc_name );
  docI->setSeries( doc_series );
  docI->setNumber( doc_number );
  docI->setDate( doc_date );
  docI->setExpiresDate( doc_expires );
  docI->setAgency( doc_agency );
  docI->setCreateDate( doc_createdate );
  instances << docI;
  return docI;
}

void MFCDocumentInfo::setType( const QString &doc_type )
{
  m__Type = doc_type;
  emit propertyChanged( "type", doc_type );
}

void MFCDocumentInfo::setName( const QString &doc_name )
{
  m__Name = doc_name;
  emit propertyChanged( "name", doc_name );
}

void MFCDocumentInfo::setSeries( const QString &doc_series )
{
  m__Series = doc_series;
  emit propertyChanged( "series", doc_series );
}

void MFCDocumentInfo::setNumber( const QString &doc_number )
{
  m__Number = doc_number;
  emit propertyChanged( "number", doc_number );
}

void MFCDocumentInfo::setDate( QDate doc_date )
{
  m__Date = doc_date;
  emit propertyChanged( "date", doc_date );
}

void MFCDocumentInfo::setExpiresDate( QDate doc_expires )
{
  m__Expires = doc_expires;
  emit propertyChanged( "expires", doc_expires );
}

void MFCDocumentInfo::setAgency( const QString &doc_agency )
{
  m__Agency = doc_agency;
  emit propertyChanged( "agency", doc_agency );
}

void MFCDocumentInfo::setUrl( const QString &doc_url )
{
  m__Url = doc_url;
  emit propertyChanged( "url", doc_url );
}

void MFCDocumentInfo::setLocalFile( const QString &doc_localFile )
{
  m__LocalFile = doc_localFile;
  emit propertyChanged( "localFile", doc_localFile );
}

void MFCDocumentInfo::setCreateDate( QDateTime doc_createdate )
{
  m__CreateDate = doc_createdate;
  emit propertyChanged( "created", doc_createdate );
}

const QString & MFCDocumentInfo::type()
{
  return m__Type;
}

const QString & MFCDocumentInfo::name()
{
  return m__Name;
}

const QString & MFCDocumentInfo::series()
{
  return m__Series;
}

const QString & MFCDocumentInfo::number()
{
  return m__Number;
}

const QDate & MFCDocumentInfo::date()
{
  return m__Date;
}

const QDate & MFCDocumentInfo::expiresDate()
{
  return m__Expires;
}

const QString & MFCDocumentInfo::agency()
{
  return m__Agency;
}

const QString & MFCDocumentInfo::url()
{
  return m__Url;
}

const QString & MFCDocumentInfo::localFile()
{
  return m__LocalFile;
}

const QDateTime & MFCDocumentInfo::createDate()
{
  return m__CreateDate;
}

void MFCDocumentInfo::remove( MFCDocumentInfo *doc )
{
  if( instances.contains( doc ) )
  {
    instances.removeOne(doc);
    delete doc;
    doc = NULL;
  }
}

MFCDocumentInfo::MFCDocumentInfo( QObject *parent ) :
  QObject( parent )
{
  m__Type = QString();
  m__Name = QString();
  m__Series = QString();
  m__Number = QString();
  m__Date = QDate();
  m__Expires = QDate();
  m__Agency = QString();
  m__Url = QString();
  m__LocalFile = QString();
  m__CreateDate = QDateTime::currentDateTime();
  connect( this, SIGNAL(destroyed()), SLOT(remove()) );
}

MFCDocumentInfo::~MFCDocumentInfo()
{

}

void MFCDocumentInfo::remove()
{
  remove( this );
}
