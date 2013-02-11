#include "mrowcalculationalgorithm.h"

#include "mrowcalculationalgorithmprivate.h"
#include "mucalculator.h"
#include "mcalculationalrow.h"


MRowCalculationAlgorithm::MRowCalculationAlgorithm( MCalculationalRow *writableRow ) :
  MAbstractRowCalculationAlgorithm( writableRow )
{
  p = new MRowCalculationAlgorithmPrivate;
}

bool MRowCalculationAlgorithm::setAlgorithm( const QString &algorithm )
{
  if ( algorithm.simplified().isEmpty() ) return false;

  p->m__Algorithm = algorithm.simplified();

  return true;
}

const QString & MRowCalculationAlgorithm::algorithm() const
{
  return p->m__Algorithm;
}

void MRowCalculationAlgorithm::calculateColumn( int column )
{
  QString calc = p->m__Algorithm;
  for ( int idx = 0; idx < readableRows().count(); idx++ )
  {
    QVariant val = readableRows()[idx]->data( column );
    QString value = "0";
    if ( val.type() == QVariant::String )
      value = val.toString().toInt();
    if ( val.type() == QVariant::Double )
      value = QString::number( val.toDouble() );
    if ( val.type() == QVariant::Int )
      value = QString::number( val.toInt() );
    if ( val.type() == QVariant::LongLong )
      value = QString::number( val.toLongLong() );
    if ( val.type() == QVariant::UInt )
      value = QString::number( val.toUInt() );
    if ( val.type() == QVariant::ULongLong )
      value = QString::number( val.toULongLong() );
    calc = calc.replace( tr( "col[%1]" ).arg( (idx+1) ), value );
  }

  QVariant result = 0;

}
