#include "mucalculator.h"

#include "muParser.h"

#include <QDebug>

muCalculator::muCalculator()
{
}

QVariant muCalculator::calc( QString expression, int decCount )
{
  QVariant result_buffer = QVariant();
  mu::Parser p;
  mu::string_type expression_buffer;
  QByteArray expression_array = expression.toLocal8Bit();
  char *expression_chars = expression_array.data();
  expression_buffer = expression_chars;
  try
  {
    p.SetExpr(expression_buffer);
    double result = p.Eval();
//    char buffer[expression_array.size()+1];
//    sprintf(buffer,"%f",result);
//    result_buffer = buffer;
    result_buffer=QObject::tr("%1").arg(result).toLocal8Bit().constData();
  }
  catch(mu::Parser::exception_type &e)
  {
    result_buffer = "error";
  }

  QString val = result_buffer.toString();
  if ( val == QObject::tr( "inf" ) ||
       val == QObject::tr( "nan" ) ) return 0;
  if ( val != QObject::tr( "error" ) )
  {
    double dVal = val.toDouble();
    if ( decCount > -1 ) dVal = round( dVal, decCount );
//    while ( val.length() > 1 && val.right( 1 ) == "0" )
//      val = val.mid( 0, val.length()-1 );
//    if ( decCount > -1 )
//    {
//      int dotIndex = val.indexOf( "." );
//      if ( dotIndex > -1 )
//        while ( val.length()-(dotIndex+1) > decCount )
//          val = val.mid( 0, val.length()-1 );
//    }
    if ( !QString::number( dVal ).contains( "." ) )
      return (qint64)dVal;
    else return dVal;
  }

  return result_buffer;
}

double muCalculator::round( double value, int decCount )
{
  QString sdec = "";
  while ( sdec.length() < decCount )
    sdec += "0";
  double s_inc = QString( "1%1" ).arg( sdec ).toDouble();

  return (double)qRound(value*s_inc)/s_inc;
}
