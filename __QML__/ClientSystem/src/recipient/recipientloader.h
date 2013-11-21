#ifndef RECIPIENTLOADER_H
#define RECIPIENTLOADER_H

#include <QObject>

#include <QtQml>


class RecipientLoader_P;
class RecipientList;
class Recipient;

class RecipientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RecipientLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(RecipientList* source READ source NOTIFY sourceChanged)


  public:
    RecipientLoader(QObject *parent = 0);
    ~RecipientLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Recipient * create() const;

    RecipientList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    RecipientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(RecipientLoader)

#endif // RECIPIENTLOADER_H
