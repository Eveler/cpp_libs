#include "countriesstorage.h"

CountriesStorage *CountriesStorage::m__Instance = NULL;

CountriesStorage * CountriesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new CountriesStorage;

  return m__Instance;
}

CountriesStorage::CountriesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

