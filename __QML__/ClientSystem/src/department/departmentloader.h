#ifndef DEPARTMENTLOADER_H
#define DEPARTMENTLOADER_H

#include <QObject>

#include <QtQml>


class DepartmentLoader_P;
class DepartmentList;
class Department;

class DepartmentLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DepartmentLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(DepartmentList* source READ source NOTIFY sourceChanged)


  public:
    DepartmentLoader(QObject *parent = 0);
    ~DepartmentLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Department * create() const;

    DepartmentList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    DepartmentLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(DepartmentLoader)

#endif // DEPARTMENTLOADER_H
