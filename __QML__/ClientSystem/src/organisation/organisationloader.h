#ifndef ORGANISATIONLOADER_H
#define ORGANISATIONLOADER_H

#include <QObject>

#include <QtQml>


class OrganisationLoader_P;
class OrganisationList;
class Organisation;

class OrganisationLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OrganisationLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(OrganisationList* source READ source NOTIFY sourceChanged)


  public:
    OrganisationLoader(QObject *parent = 0);
    ~OrganisationLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Organisation * create() const;

    OrganisationList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    OrganisationLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(OrganisationLoader)

#endif // ORGANISATIONLOADER_H
