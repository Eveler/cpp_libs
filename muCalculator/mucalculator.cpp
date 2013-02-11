#include "mucalculator.h"

#include "muParser.h"


muCalculator::muCalculator()
{
}

QVariant muCalculator::calc( QString expression )
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

  return result_buffer;
}
