#include "mucalculator.h"

#include "muParser.h"


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
    char buffer[expression_array.size()+1];
    sprintf(buffer,"%f",result);
    result_buffer = buffer;
  }
  catch(mu::Parser::exception_type &e)
  {
    result_buffer = "error";
  }


  QString val = result_buffer.toString();
  if ( val != QObject::tr( "error" ) )
  {
    while ( val.length() > 1 && val.right( 1 ) == "0" )
      val = val.mid( 0, val.length()-1 );
    if ( decCount > -1 )
    {
      int dotIndex = val.indexOf( "." );
      if ( dotIndex > -1 )
        while ( val.length()-(dotIndex+1) > decCount )
          val = val.mid( 0, val.length()-1 );
    }
    if ( val.right( 1 ) == "." )
      val = val.mid( 0, val.length()-1 );
    result_buffer = val;
  }

  return result_buffer;
}
