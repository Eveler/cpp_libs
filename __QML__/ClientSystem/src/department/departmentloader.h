#ifndef DEPARTMENTLOADER_H
#define DEPARTMENTLOADER_H

#include <QObject>

#include <QtQml>


class DepartmentLoader_P;
class DepartmentInfo;

class DepartmentLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DepartmentLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    DepartmentLoader(QObject *parent = 0);
    ~DepartmentLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( DepartmentInfo *info );


  public slots:


  private:
    DepartmentLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DepartmentLoader)

#endif // DEPARTMENTLOADER_H
