#ifndef QMLDOCUMENTLOADER_P_H
#define QMLDOCUMENTLOADER_P_H

#include <QObject>

#include "docmanager.h"


class QMLDocumentLoader_P : public QObject
{
    Q_OBJECT

public:
    static QMLDocumentLoader_P * instance();

    const QList<QString> & documents() const;

    void loadDocument( int declarId, int docIndex, QString connectionName );


signals:
    void documentsChanged();


public slots:


private:
    static QMLDocumentLoader_P *m__Instance;
    QList<QString> m__Documents;
    QHash<QString, Docmanager *> m__Docmanagers;

    explicit QMLDocumentLoader_P();
};

#endif // QMLDOCUMENTLOADER_P_H
