#ifndef MUCALCULATOR_H
#define MUCALCULATOR_H

#include "export/mucalculator_export_lib.h"

#include <QVariant>


class EXPORT_MUCALCULATOR muCalculator
{
public:
  muCalculator();

  static QVariant calc( QString expression , int decCount = -1 );
  static double round( double value, int decCount = 0 );
};

#endif // MUCALCULATOR_H
