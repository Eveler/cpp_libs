#ifndef QMLDOCUMENTLOADER_H
#define QMLDOCUMENTLOADER_H

#include <QQuickItem>


class QMLDocumentLoader_P;

class QMLDocumentLoader : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QMLDocumentLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(QList<QString> documents READ documents NOTIFY documentsChanged)

public:
    explicit QMLDocumentLoader(QQuickItem *parent = 0);

    QString connectionName();
    void setConnectionName( QString connectionName );

    const QList<QString> & documents() const;

    Q_INVOKABLE void setDeclar( int delcarId );
    Q_INVOKABLE void loadDocument( int docIndex );


signals:
    void documentsChanged();
    void connectionNameChanged();


public slots:


private:
    QMLDocumentLoader_P *p;

    QString m__ConnectionName;
};

#endif // QMLDOCUMENTLOADER_H
