#ifndef USERLOADER_H
#define USERLOADER_H

#include <QObject>

#include <QtQml>


class UserLoader_P;
class UserList;
class User;

class UserLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UserLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(UserList* source READ source NOTIFY sourceChanged)


public:
    UserLoader(QObject *parent = 0);
    ~UserLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load() const;
    Q_INVOKABLE User * create() const;

    UserList * source() const;


signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


public slots:


private:
    UserLoader_P *p;
    QEventLoop *loop;

private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(UserLoader)

static QObject * userLoader_Provider( QQmlEngine *engine, QJSEngine *scriptEngine )
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new UserLoader();
}

#endif // USERLOADER_H
