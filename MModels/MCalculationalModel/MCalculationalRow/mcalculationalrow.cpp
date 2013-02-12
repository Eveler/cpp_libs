#include "mcalculationalrow.h"

#include "mcalculationalrowprivate.h"
#include "mcalculationalmodel.h"
#include "mcalculationalcolumn.h"


int MCalculationalRow::sectionCount() const
{
  return p->m__Model->columnCount();
}

QVariant MCalculationalRow::data( int column )
{
  if ( column < 0 || column >= p->m__Model->columnCount() ) return QVariant();

  MCalculationalColumn *c = p->m__Model->column( column );
  if ( c == NULL ) return QVariant();

  return c->data( row() );
}

bool MCalculationalRow::setData( int column, QVariant value )
{
  if ( column < 0 || column >= p->m__Model->columnCount() ) return false;

  if ( p->hasAlgorithmForSection( column ) ) return false;

  p->m__Model->column( column )->setData( row(), value );

  return true;
}

MCalculationalModel * MCalculationalRow::model() const
{
  return p->m__Model;
}

int MCalculationalRow::row()
{
  return p->m__Model->findRow( this );
}

MCalculationalRow::MCalculationalRow( MCalculationalModel *model ) :
  QObject(model)
{
  p = new MCalculationalRowPrivate( model );
}

MCalculationalRow::~MCalculationalRow()
{
  delete p;
  p = NULL;
}

void MCalculationalRow::addRowAlgorithm( MAbstractRowCalculationAlgorithm *algorithm )
{
  p->m__RowAlgorithms << algorithm;
}
