#ifndef TRUSTEELOADER_H
#define TRUSTEELOADER_H

#include <QObject>

#include <QtQml>


class TrusteeLoader_P;
class TrusteeList;
class Trustee;

class TrusteeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TrusteeLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(TrusteeList* source READ source NOTIFY sourceChanged)


  public:
    TrusteeLoader(QObject *parent = 0);
    ~TrusteeLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Trustee * create() const;

    TrusteeList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    TrusteeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(TrusteeLoader)

#endif // TRUSTEELOADER_H
