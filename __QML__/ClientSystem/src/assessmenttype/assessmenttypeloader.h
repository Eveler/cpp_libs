#ifndef ASSESSMENTTYPELOADER_H
#define ASSESSMENTTYPELOADER_H

#include <QObject>

#include <QtQml>


class AssessmenttypeLoader_P;
class AssessmenttypeList;
class Assessmenttype;

class AssessmenttypeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmenttypeLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(AssessmenttypeList* source READ source NOTIFY sourceChanged)


  public:
    AssessmenttypeLoader(QObject *parent = 0);
    ~AssessmenttypeLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Assessmenttype * create() const;

    AssessmenttypeList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    AssessmenttypeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(AssessmenttypeLoader)

#endif // ASSESSMENTTYPELOADER_H
