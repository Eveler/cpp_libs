#include "mfcdocumentioprovider.h"


MFCDocumentIOProvider::MFCDocumentIOProvider()
{

}

MFCDocumentIOProvider::~MFCDocumentIOProvider()
{
  m__Error.clear();
}

const QString & MFCDocumentIOProvider::error() const
{
  return m__Error;
}

void MFCDocumentIOProvider::setError( const QString &error )
{
  m__Error = error;
}
