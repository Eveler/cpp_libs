#include "slaveaddressesstorage.h"

SlaveAddressesStorage *SlaveAddressesStorage::m__Instance = NULL;

SlaveAddressesStorage * SlaveAddressesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new SlaveAddressesStorage;

  return m__Instance;
}

SlaveAddressesStorage::SlaveAddressesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

