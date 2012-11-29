#ifndef PROCEDURESSTORAGE_H
#define PROCEDURESSTORAGE_H

#include "abstractsimplestorage.h"
#include "procedure.h"

class ProceduresStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static ProceduresStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static ProceduresStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Procedures;

  explicit ProceduresStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // PROCEDURESSTORAGE_H
