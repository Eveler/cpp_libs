#ifndef DECLARLOADER_H
#define DECLARLOADER_H

#include <QObject>

#include <QtQml>


class DeclarLoader_P;
class DeclarList;
class Declar;

class DeclarLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(DeclarList* source READ source NOTIFY sourceChanged)


  public:
    DeclarLoader(QObject *parent = 0);
    ~DeclarLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Declar * create() const;

    DeclarList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    DeclarLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(DeclarLoader)

#endif // DECLARLOADER_H
