#ifndef MFCCORE_H
#define MFCCORE_H

#include <QAbstractItemModel>

class MFCCore
{
public:
  static int findColumn( QAbstractItemModel *model, const QString &name );
};

#endif // MFCCORE_H
