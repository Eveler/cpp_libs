#ifndef SERVICELOADER_H
#define SERVICELOADER_H

#include <QObject>

#include <QtQml>


class ServiceLoader_P;
class ServiceList;
class Service;

class ServiceLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServiceLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(ServiceList* source READ source NOTIFY sourceChanged)


  public:
    ServiceLoader(QObject *parent = 0);
    ~ServiceLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Service * create() const;

    ServiceList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    ServiceLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(ServiceLoader)

#endif // SERVICELOADER_H
