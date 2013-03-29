#ifndef OFFICE_H
#define OFFICE_H

#include "abstractsimpleobject.h"

#include "export/office_export_lib.h"


class Office_P;
class OfficesStorage;

class EXPORT_OFFICE Office : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Office_P;
  friend class OfficesStorage;


public:
  ~Office();

  void setName( const QString &name );
  const QString & name() const;


signals:
  void nameChanged();


public slots:


private:
  Office_P *p;

  explicit Office( QVariant id, QObject *parent = 0 );
};

#endif // OFFICE_H
