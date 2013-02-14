#include "mcolumncalculationalgorithm.h"

#include "mcolumncalculationalgorithmprivate.h"
#include "mucalculator.h"
#include "mcalculationalcolumn.h"
#include "mcalculationalrow.h"
#include "mcalculationalmodel.h"

#include <QDebug>


MColumnCalculationAlgorithm::MColumnCalculationAlgorithm(
    MCalculationalColumn *writableColumn ) :
  MAbstractColumnCalculationAlgorithm( writableColumn )
{
  p = new MColumnCalculationAlgorithmPrivate;
}

MColumnCalculationAlgorithm::~MColumnCalculationAlgorithm()
{
  delete p;
  p = NULL;
}

bool MColumnCalculationAlgorithm::setAlgorithm( const QString &algorithm, int decCount )
{
  if ( algorithm.simplified().isEmpty() ) return false;

  QVariant result = muCalculator::calc(
        algorithm.simplified().replace( tr( "[" ), "" ).replace(
          tr( "]" ), "" ).replace( tr( "col" ), "" ) );
  if ( result.toString() == tr( "error" ) ) return false;

  p->m__Algorithm = algorithm.simplified();
  p->m__DecCount = decCount;

  calculate();

  return true;
}

const QString & MColumnCalculationAlgorithm::algorithm() const
{
  return p->m__Algorithm;
}

void MColumnCalculationAlgorithm::calculateRow( int row )
{
  QString algorithm = p->m__Algorithm;
  for ( int idx = 0; idx < readableColumns().count(); idx++ )
  {
    QVariant val = readableColumns()[idx]->data( row );
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
    algorithm = algorithm.replace( tr( "[col%1]" ).arg( (idx+1) ), value );
  }

  QVariant result = muCalculator::calc( algorithm, p->m__DecCount );
//  if ( writableColumn()->model()->column(
//         0 )->data( row ).toString() == tr( "2.2М" ) )
//  {
//    qDebug() << algorithm;
//    qDebug() << result;
//  }
  if ( result.toString() == tr( "error" ) ) setData( row, 0 );
  else setData( row, result );
}
