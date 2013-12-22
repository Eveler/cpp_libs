#ifndef ORGANISATIONLOADER_H
#define ORGANISATIONLOADER_H

#include <QObject>

#include <QtQml>


class OrganisationLoader_P;
class OrganisationInfo;

class OrganisationLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OrganisationLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)


  public:
    OrganisationLoader(QObject *parent = 0);
    ~OrganisationLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( OrganisationInfo *info );


  public slots:


  private:
    OrganisationLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(OrganisationLoader)

#endif // ORGANISATIONLOADER_H
