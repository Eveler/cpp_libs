#ifndef CLIENTLOADER_H
#define CLIENTLOADER_H

#include <QObject>

#include <QtQml>


class ClientLoader_P;
class ClientList;
class Client;

class ClientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ClientLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(ClientList* source READ source NOTIFY sourceChanged)


  public:
    ClientLoader(QObject *parent = 0);
    ~ClientLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Client * create() const;

    ClientList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    ClientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(ClientLoader)

#endif // CLIENTLOADER_H
