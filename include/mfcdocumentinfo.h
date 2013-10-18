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
    Q_PROPERTY(int originalExemplars READ originalExemplars WRITE setOriginalExemplars)
    Q_PROPERTY(int originalPages READ originalPages WRITE setOriginalPages)
    Q_PROPERTY(int copyExemplars READ copyExemplars WRITE setCopyExemplars)
    Q_PROPERTY(int copyPages READ copyPages WRITE setCopyPages)
    Q_PROPERTY(QString url READ url WRITE setUrl)
    Q_PROPERTY(QString localFile READ localFile WRITE setLocalFile)
    Q_PROPERTY(QDateTime created READ createDate WRITE setCreateDate)
    Q_PROPERTY(bool initial READ initial WRITE setInitial)


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
    void setOriginalExemplars( int doc_oexemplars );
    void setOriginalPages( int doc_opages );
    void setCopyExemplars( int doc_cexemplars );
    void setCopyPages( int doc_cpages );
    void setUrl( const QString &doc_url );
    void setLocalFile( const QString &doc_localFile );
    void setCreateDate( QDateTime doc_createdate );
    void setInitial( bool doc_initial );

    const QString & type() const;
    const QString & name() const;
    const QString & series() const;
    const QString & number() const;
    const QDate & date() const;
    const QDate & expiresDate() const;
    const QString & agency() const;
    int originalExemplars() const;
    int originalPages() const;
    int copyExemplars() const;
    int copyPages() const;
    const QString & url() const;
    const QString & localFile() const;
    const QDateTime & createDate() const;
    bool initial() const;

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
    int m__OriginalExemplars;
    int m__OriginalPages;
    int m__CopyExemplars;
    int m__CopyPages;
    QString m__Url;
    QString m__LocalFile;
    QDateTime m__CreateDate;
    bool m__Initial;

    explicit MFCDocumentInfo( QObject *parent );
    ~MFCDocumentInfo();

  private slots:
    void remove();
};

#endif // MFCDOCUMENTINFO_H
