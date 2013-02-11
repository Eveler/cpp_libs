#ifndef MUCALCULATOR_H
#define MUCALCULATOR_H

#include "lib_export.h"

#include <QVariant>


class EXPORT muCalculator
{
public:
  muCalculator();

  static QVariant calc( QString expression );
};

#endif // MUCALCULATOR_H
