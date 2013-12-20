#ifndef PROCEDURELOADER_H
#define PROCEDURELOADER_H

#include <QObject>

#include <QtQml>


class ProcedureLoader_P;
class ProcedureInfo;

class ProcedureLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcedureLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    ProcedureLoader(QObject *parent = 0);
    ~ProcedureLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( ProcedureInfo *info );


  public slots:


  private:
    ProcedureLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ProcedureLoader)

#endif // PROCEDURELOADER_H
