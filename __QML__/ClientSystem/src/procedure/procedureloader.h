#ifndef PROCEDURELOADER_H
#define PROCEDURELOADER_H

#include <QObject>

#include <QtQml>


class ProcedureLoader_P;
class ProcedureList;
class Procedure;

class ProcedureLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcedureLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(ProcedureList* source READ source NOTIFY sourceChanged)


  public:
    ProcedureLoader(QObject *parent = 0);
    ~ProcedureLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Procedure * create() const;

    ProcedureList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    ProcedureLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(ProcedureLoader)

#endif // PROCEDURELOADER_H
