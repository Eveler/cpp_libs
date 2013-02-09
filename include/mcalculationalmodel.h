#ifndef MCALCULATIONALMODEL_H
#define MCALCULATIONALMODEL_H

#include <QAbstractItemModel>

#include "lib_export.h"


class EXPORT MCalculationalModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit MCalculationalModel(QObject *parent = 0);

signals:

public slots:

};

#endif // MCALCULATIONALMODEL_H
