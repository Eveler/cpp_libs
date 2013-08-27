#ifndef QMLDOCUMENTLOADER_H
#define QMLDOCUMENTLOADER_H

#include <QQuickItem>


class Docmanager;

class QMLDocumentLoader : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QMLDocumentLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

public:
    explicit QMLDocumentLoader(QQuickItem *parent = 0);

    QString connectionName();
    void setConnectionName( QString connectionName );

    int count();
    int progress() const;

    Q_INVOKABLE void loadDocuments( int declarId );
    Q_INVOKABLE QString document( int index );


signals:
    void connectionNameChanged();
    void countChanged();
    void progressChanged();


public slots:


private:
    QString m__ConnectionName;
    Docmanager *m__Docmanager;
    int m__DataTransferProgress;


private slots:
    void dataTransferProgress( qint64 current,qint64 total );
};

#endif // QMLDOCUMENTLOADER_H
