#ifndef MFCDOCUMENTIOPROVIDER_H
#define MFCDOCUMENTIOPROVIDER_H

#include "export/dossier_export.h"

#include <QString>


class MFCDocument;

class DOSSIER_EXPORT MFCDocumentIOProvider
{
  public:
    MFCDocumentIOProvider();
    ~MFCDocumentIOProvider();

    virtual bool load( MFCDocument *doc ) = 0;
    virtual bool save( MFCDocument *doc ) = 0;

    const QString & error() const;

  protected:
    void setError( const QString &error );


  private:
    QString m__Error;
};

#endif // MFCDOCUMENTIOPROVIDER_H
