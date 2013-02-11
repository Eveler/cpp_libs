#ifndef QMATHPARSER_H
#define QMATHPARSER_H

#include "lib_export.h"

#include <QVariant>


class EXPORT QMathParser
{
public:
  QMathParser();

  static QVariant parse( QString expression );
};

#endif // QMATHPARSER_H
