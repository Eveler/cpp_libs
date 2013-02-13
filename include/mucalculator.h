#ifndef MUCALCULATOR_H
#define MUCALCULATOR_H

#include "lib_export.h"

#include <QVariant>


class EXPORT muCalculator
{
public:
  muCalculator();

  static QVariant calc( QString expression , int decCount = -1 );
  static double round( double value, int decCount = 0 );
};

#endif // MUCALCULATOR_H
