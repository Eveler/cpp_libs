#ifndef SMSSTORAGE_H
#define SMSSTORAGE_H

#include "abstractsimplestorage.h"

class SmsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static SmsStorage * instance();

signals:

public slots:

private:
  static SmsStorage *m__Instance;

  explicit SmsStorage(QObject *parent = 0);

};

#endif // SMSSTORAGE_H
