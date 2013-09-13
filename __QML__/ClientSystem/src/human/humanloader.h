#ifndef HUMANLOADER_H
#define HUMANLOADER_H

#include <QObject>

#include <QtQml>


class HumanLoader_P;
class HumanList;
class Human;

class HumanLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HumanLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(HumanList* source READ source WRITE setSource NOTIFY sourceChanged)


public:
    HumanLoader(QObject *parent = 0);
    ~HumanLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load() const;
    Q_INVOKABLE Human * create() const;

    HumanList * source() const;
    void setSource( HumanList * source ) const;


signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


public slots:


private:
    HumanLoader_P *p;
    QEventLoop *loop;

private slots:
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(HumanLoader)

#endif // HUMANLOADER_H
