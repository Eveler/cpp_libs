#ifndef declarCLIENTLOADER_H
#define declarCLIENTLOADER_H

#include <QObject>

#include <QtQml>


class DeclarClientLoader_P;
class DeclarClientList;
class DeclarClient;

class DeclarClientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarClientLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(DeclarClientList* source READ source NOTIFY sourceChanged)


  public:
    DeclarClientLoader(QObject *parent = 0);
    ~DeclarClientLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE DeclarClient * create() const;

    DeclarClientList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    DeclarClientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(DeclarClientLoader)

#endif // declarCLIENTLOADER_H
