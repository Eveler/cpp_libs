#include "proceduresstorage.h"

ProceduresStorage *ProceduresStorage::m__Instance = NULL;

ProceduresStorage * ProceduresStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new ProceduresStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & ProceduresStorage::objects() const
{
  return m__Procedures;
}

ProceduresStorage::ProceduresStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void ProceduresStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__ColName_Id ) );
  obj->setName( record->currentProperty( m__ColName_Name ).toString() );
}

void ProceduresStorage::recordAdded( MFCRecord *record, int index )
{
  Procedure *procedure = new Procedure( this );
  setObjectData( procedure, record );
  m__Procedures.insert( index, procedure );
}

void ProceduresStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Procedures.removeAt( index );
}
