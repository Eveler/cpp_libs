#ifndef OFFICESSTORAGE_H
#define OFFICESSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/office_export_lib.h"


class Office;

typedef QList<Office *> OfficeList;

class EXPORT_OFFICE OfficesStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static OfficesStorage * instance();

  const OfficeList & offices() const;

  AbstractSimpleObjectList findByName( AbstractSimpleObjectList objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static OfficesStorage *m__Instance;

  explicit OfficesStorage(QObject *parent = 0);
};

#endif // OFFICESSTORAGE_H
