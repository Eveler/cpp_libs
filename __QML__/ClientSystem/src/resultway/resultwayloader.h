#ifndef RESULTWAYLOADER_H
#define RESULTWAYLOADER_H

#include <QObject>

#include <QtQml>


class ResultwayLoader_P;
class ResultwayList;
class Resultway;

class ResultwayLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultwayLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(ResultwayList* source READ source NOTIFY sourceChanged)


  public:
    ResultwayLoader(QObject *parent = 0);
    ~ResultwayLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Resultway * create() const;

    ResultwayList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    ResultwayLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(ResultwayLoader)

#endif // RESULTWAYLOADER_H
