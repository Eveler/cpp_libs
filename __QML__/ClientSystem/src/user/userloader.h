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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)


  public:
    UserLoader(QObject *parent = 0);
    ~UserLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    Q_INVOKABLE bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( UserInfo *info );


  public slots:


  private:
    UserLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(UserLoader)

#endif // USERLOADER_H
