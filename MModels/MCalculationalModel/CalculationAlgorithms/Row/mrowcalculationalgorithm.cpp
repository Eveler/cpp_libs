#include "mrowcalculationalgorithm.h"

#include "mrowcalculationalgorithmprivate.h"
#include "mucalculator.h"
#include "mcalculationalcolumn.h"
#include "mcalculationalrow.h"
#include "mcalculationalmodel.h"

#if QT_VERSION >= 0x050000
#include "amslogger5.h"
#else
#include "amslogger.h"
#endif


MRowCalculationAlgorithm::MRowCalculationAlgorithm( MCalculationalRow *writableRow ) :
  MAbstractRowCalculationAlgorithm( writableRow )
{
  p = new MRowCalculationAlgorithmPrivate;
}

MRowCalculationAlgorithm::~MRowCalculationAlgorithm()
{
  delete p;
  p = NULL;
}

bool MRowCalculationAlgorithm::setAlgorithm( const QString &algorithm, int decCount )
{
  if ( algorithm.simplified().isEmpty() ) return false;

  QVariant result = muCalculator::calc(
        algorithm.simplified().replace( tr( "[" ), "" ).replace(
          tr( "]" ), "" ).replace( tr( "row" ), "" ) );
  if ( result.toString() == tr( "error" ) ) return false;

  p->m__Algorithm = algorithm.simplified();
  p->m__DecCount = decCount;

  calculate();

  return true;
}

const QString & MRowCalculationAlgorithm::algorithm() const
{
  return p->m__Algorithm;
}

void MRowCalculationAlgorithm::calculateColumn( int column )
{
  QString algorithm = p->m__Algorithm;
  for ( int idx = 0; idx < readableRows().count(); idx++ )
  {
    QVariant val = readableRows()[idx]->data( column );
    QString value = "0";
    if ( val.type() == QVariant::String )
      value = QString::number( val.toString().toInt() );
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
    QString key = tr( "[row%1]" ).arg( (idx+1) );
    algorithm = algorithm.replace( key, value );
  }

  QVariant result = muCalculator::calc( algorithm, p->m__DecCount );
  if ( result.toString() == tr( "error" ) ) setData( column, 0 );
  else setData( column, result );
}
