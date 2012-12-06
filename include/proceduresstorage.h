#ifndef PROCEDURESSTORAGE_H
#define PROCEDURESSTORAGE_H

#include "abstractsimplestorage.h"

class ProceduresStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static ProceduresStorage * instance();

signals:

public slots:

private:
  static ProceduresStorage *m__Instance;

  explicit ProceduresStorage(QObject *parent = 0);

};

#endif // PROCEDURESSTORAGE_H
