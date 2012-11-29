#ifndef DESTINATIONSSTORAGE_H
#define DESTINATIONSSTORAGE_H

#include "abstractsimplestorage.h"
#include "destination.h"

class DestinationsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static DestinationsStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static DestinationsStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Destinations;

  explicit DestinationsStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // DESTINATIONSSTORAGE_H
