#ifndef OFFICESSTORAGE_H
#define OFFICESSTORAGE_H

#include "abstractsimplestorage.h"
#include "office.h"

class OfficesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static OfficesStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static OfficesStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Offices;

  explicit OfficesStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // OFFICESSTORAGE_H
