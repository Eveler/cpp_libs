#include "mcalculationalrow.h"

#include "mcalculationalrowprivate.h"


int MCalculationalRow::sectionCount() const
{
  return p->m__Data.count();
}

QVariant MCalculationalRow::data( int section ) const
{
  if ( section < 0 || section >= p->m__Data.count() ) return QVariant();

  return p->m__Data[section];
}

bool MCalculationalRow::setData( int section, QVariant value )
{
  if ( section < 0 || section >= p->m__Data.count() ) return false;

  QVariant oldValue = p->m__Data[section];
  p->m__Data[section] = value;

  emit dataChanged( section, oldValue, value );

  return true;
}

MCalculationalRow::MCalculationalRow( int count, QObject *parent ) :
  QObject(parent)
{
  p = new MCalculationalRowPrivate( count );
}

MCalculationalRow::~MCalculationalRow()
{
  delete p;
  p = NULL;
}

void MCalculationalRow::insert( int section )
{
  p->m__Data.insert( section, QVariant() );
}

void MCalculationalRow::remove( int section )
{
  p->m__Data.removeAt( section );
}
