#ifndef MFCDOCUMENTINFO_H
#define MFCDOCUMENTINFO_H

#include <QObject>

#include "export/dossier_export.h"

#include <QString>
#include <QDateTime>
#include <QVariant>


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
    Q_PROPERTY(QString url READ url WRITE setUrl)
    Q_PROPERTY(QString localFile READ localFile WRITE setLocalFile)
    Q_PROPERTY(QString agency READ agency WRITE setAgency)
    Q_PROPERTY(QDateTime created READ createDate WRITE setCreateDate)


  public:
    static MFCDocumentInfo * instance(
        QString doc_type = QString(), QString doc_name = QString(),
        QString doc_series = QString(), QString doc_number = QString(),
        QDate doc_date = QDate(), QDate doc_expires = QDate(),
        QString doc_agency = QString(),
        QDateTime doc_createdate = QDateTime::currentDateTime(),
        QObject *parent = NULL );

    void setType( const QString &doc_type );
    void setName( const QString &doc_name );
    void setSeries( const QString &doc_series );
    void setNumber( const QString &doc_number );
    void setDate( QDate doc_date );
    void setExpiresDate( QDate doc_expires );
    void setAgency( const QString &doc_agency );
    void setUrl( const QString &doc_url );
    void setLocalFile( const QString &doc_localFile );
    void setCreateDate( QDateTime doc_createdate );

    const QString & type();
    const QString & name();
    const QString & series();
    const QString & number();
    const QDate & date();
    const QDate & expiresDate();
    const QString & agency();
    const QString & url();
    const QString & localFile();
    const QDateTime & createDate();

    bool isValid();


  public slots:
    static void remove( MFCDocumentInfo *docInfo );


  signals:
    void propertyChanged( QString pName, QVariant pVal );


  private:
    static QList<MFCDocumentInfo *> instances;
    QString m__Type;
    QString m__Name;
    QString m__Series;
    QString m__Number;
    QDate m__Date;
    QDate m__Expires;
    QString m__Agency;
    QString m__Url;
    QString m__LocalFile;
    QDateTime m__CreateDate;

    explicit MFCDocumentInfo( QObject *parent );
    ~MFCDocumentInfo();

  private slots:
    void remove();
};

#endif // MFCDOCUMENTINFO_H
