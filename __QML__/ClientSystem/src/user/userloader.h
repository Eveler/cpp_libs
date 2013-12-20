#ifndef USERLOADER_H
#define USERLOADER_H

#include <QObject>

#include <QtQml>


class UserLoader_P;
class UserInfo;

class UserLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UserLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    UserLoader(QObject *parent = 0);
    ~UserLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    Q_INVOKABLE bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( UserInfo *info );


  public slots:


  private:
    UserLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(UserLoader)

#endif // USERLOADER_H
