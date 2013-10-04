#ifndef MFCDOCUMENTINFO_H
#define MFCDOCUMENTINFO_H

#include <QObject>

#include "export/dossier_export.h"


class DOSSIER_EXPORT MFCDocumentInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString series READ series WRITE setSeries)
    Q_PROPERTY(QString number READ number WRITE setNumber)
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(QDate expires READ expiresDate WRITE setExpiresDate)
    Q_PROPERTY(QString agency READ agency WRITE setAgency)
    Q_PROPERTY(QDateTime created READ createDate WRITE setCreateDate)


  public:
    static MFCDocumentInfo *instance(
        QString doc_type=QString(), QString doc_name=QString(),
        QString doc_series=QString(), QString doc_number=QString(),
        QDate doc_date=QDate(),
        QDate doc_expires=QDate(),
        QString doc_agency=QString(),
        QDateTime doc_createdate=QDateTime::currentDateTime(),
        QObject *parent=0);


  private:
    explicit MFCDocumentInfo( QObject *parent = NULL );
    ~MFCDocumentInfo();
};

#endif // MFCDOCUMENTINFO_H
