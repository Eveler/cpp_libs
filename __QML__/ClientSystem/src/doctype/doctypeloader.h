#ifndef DOCTYPELOADER_H
#define DOCTYPELOADER_H

#include <QObject>

#include <QtQml>


class DoctypeLoader_P;
class DoctypeList;
class Doctype;

class DoctypeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DoctypeLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(DoctypeList* source READ source WRITE setSource NOTIFY sourceChanged)


public:
    DoctypeLoader(QObject *parent = 0);
    ~DoctypeLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load() const;
    Q_INVOKABLE Doctype * create() const;

    DoctypeList * source() const;
    void setSource( DoctypeList * source ) const;


signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


public slots:


private:
    DoctypeLoader_P *p;
    QEventLoop *loop;

private slots:
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(DoctypeLoader)

#endif // DOCTYPELOADER_H
