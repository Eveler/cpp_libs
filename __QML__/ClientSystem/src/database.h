#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <QtQml>


class Database : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Database)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    Database(QObject *parent = 0);
    ~Database();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    Q_INVOKABLE QDateTime serverTime();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();


  public slots:


  private:
    QString m__LastError;
    QString m__ConnectionName;


  private slots:
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(Database)

#endif // DATABASE_H
