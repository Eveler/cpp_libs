#ifndef QMLDOCUMENT_H
#define QMLDOCUMENT_H

#include <QQuickItem>

#include "mfcdocument.h"


class QMLDocument_P;

class QMLDocument : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QMLDocument)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int pagesCount READ pagesCount NOTIFY pagesCountChanged)
    Q_PROPERTY(int attachmentsCount READ attachmentsCount NOTIFY attachmentsCountChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString series READ series WRITE setSeries NOTIFY seriesChanged)
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QDateTime docdate READ docdate WRITE setDocdate NOTIFY docdateChanged)
    Q_PROPERTY(QDateTime docexpires READ docexpires WRITE setDocexpires NOTIFY docexpiresChanged)

public:
    QMLDocument(QQuickItem *parent = 0);
    ~QMLDocument();

    QString source() const;
    void setSource( QString source );

    int pagesCount() const;
    Q_INVOKABLE QString page( int index );

    int attachmentsCount() const;
    Q_INVOKABLE QString attachmentName( int index );
    Q_INVOKABLE bool openAttachment( int index );

    Q_INVOKABLE bool isValid() const;

    Q_INVOKABLE void resetContent();

    Q_INVOKABLE void configureScanner();
    Q_INVOKABLE void scanPage();
    Q_INVOKABLE void addPage( QUrl path );
    Q_INVOKABLE bool removablePage( int index );
    Q_INVOKABLE void removePage( int index );

    QString type() const;
    void setType( const QString &type );

    QString name() const;
    void setName( const QString &name );

    QString series() const;
    void setSeries( const QString &series );

    QString number() const;
    void setNumber( const QString &number );

    QDateTime docdate() const;
    void setDocdate ( const QDateTime &docdate );

    QDateTime docexpires() const;
    void setDocexpires( const QDateTime &docexpires );


signals:
    void sourceChanged();
    void pagesCountChanged();
    void pageAdded( int index );
    void pageRemoved( int index );
    void attachmentsCountChanged();
    void typeChanged();
    void nameChanged();
    void seriesChanged();
    void numberChanged();
    void docdateChanged();
    void docexpiresChanged();


private:
    QMLDocument_P *p;

private slots:
    void documentRemoved();
};

QML_DECLARE_TYPE(QMLDocument)

#endif // QMLDOCUMENT_H

