#include "smsstorage.h"

SmsStorage *SmsStorage::m__Instance = NULL;

SmsStorage * SmsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new SmsStorage;

  return m__Instance;
}

SmsStorage::SmsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

