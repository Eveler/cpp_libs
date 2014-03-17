#include "mdocumentdbwrapper.h"

#include "mhumandbwrapper.h"


/*
 * Begin C++ - QML class definition: *[ MDocument ]*
*/
MDocument::MDocument( QQuickItem *parent ) :
  QQuickItem( parent )
{

}

MDocument::~MDocument()
{

}

QVariant MDocument::identifier() const
{
  return m__Identifier;
}

void MDocument::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
  emit identifierChanged();
}

const QString & MDocument::name() const
{
  return m__Name;
}

void MDocument::setName( QString &name )
{
  m__Name = name;
  emit nameChanged();
}

const QString & MDocument::series() const
{
  return m__Series;
}

void MDocument::setSeries( QString &series )
{
  m__Series = series;
  emit seriesChanged();
}

const QString & MDocument::number() const
{
  return m__Number;
}

void MDocument::setNumber( QString &number )
{
  m__Number = number;
  emit numberChanged();
}

QDate MDocument::created() const
{
  return m__Created;
}

void MDocument::setCreated( QDate created )
{
  m__Created = created;
  emit createdChanged();
}

QDate MDocument::expires() const
{
  return m__Expires;
}

void MDocument::setExpires( QDate expires )
{
  m__Expires = expires;
  emit expiresChanged();
}

QUrl MDocument::source() const
{
  return m__Source;
}

void MDocument::setSource( QUrl source )
{
  m__Source = source;
  emit sourceChanged();
}
/*
 * End class definition: *[ MDocument ]*
*/


/*
 * Begin C++ class definition: *[ MDocumentDBWrapper ]*
*/
MDocumentDBWrapper::MDocumentDBWrapper( MAbstractDataSource * parent ) :
  MAbstractDBWrapper(parent)
{
}

void MDocumentDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
  if ( objectiveType == (int)HumanDocuments ) searching( objectiveValue.value<MHuman *>() );
  else MAbstractDBWrapper::job( objectiveType, objectiveValue );
}

bool MDocumentDBWrapper::searching( const QString &queryText )
{
  Q_UNUSED(queryText)
  return true;
}

bool MDocumentDBWrapper::searching( MHuman *human )
{
  return true;
}

bool MDocumentDBWrapper::initiating()
{
  return true;
}

bool MDocumentDBWrapper::saving( QObject *object )
{
  return true;
}
/*
 * End class definition: *[ MDocumentDBWrapper ]*
*/
