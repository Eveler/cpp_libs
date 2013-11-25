#ifndef RESULTLOADER_H
#define RESULTLOADER_H

#include <QObject>

#include <QtQml>


class ResultLoader_P;
class ResultList;
class Result;

class ResultLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(ResultList* source READ source NOTIFY sourceChanged)


  public:
    ResultLoader(QObject *parent = 0);
    ~ResultLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Result * create() const;

    ResultList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    ResultLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(ResultLoader)

#endif // RESULTLOADER_H
