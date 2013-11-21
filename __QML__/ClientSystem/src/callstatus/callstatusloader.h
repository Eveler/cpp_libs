#ifndef CALLSTATUSLOADER_H
#define CALLSTATUSLOADER_H

#include <QObject>

#include <QtQml>


class CallstatusLoader_P;
class CallstatusList;
class Callstatus;

class CallstatusLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CallstatusLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(CallstatusList* source READ source NOTIFY sourceChanged)


  public:
    CallstatusLoader(QObject *parent = 0);
    ~CallstatusLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load() const;
    Q_INVOKABLE bool load( QVariant identifier ) const;
    Q_INVOKABLE Callstatus * create() const;

    CallstatusList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    CallstatusLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(CallstatusLoader)

#endif // CALLSTATUSLOADER_H
