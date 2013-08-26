#include "qmldocumentloader_p.h"

#include <QSqlDatabase>


QMLDocumentLoader_P *QMLDocumentLoader_P::m__Instance = NULL;

QMLDocumentLoader_P * QMLDocumentLoader_P::instance()
{
    if ( m__Instance == NULL )
        m__Instance = new QMLDocumentLoader_P();

    return m__Instance;
}

const QList<QString> & QMLDocumentLoader_P::documents() const
{
    return m__Documents;
}

void QMLDocumentLoader_P::loadDocument( int declarId, int docIndex, QString connectionName )
{
    QSqlDatabase db = QSqlDatabase::database( connectionName );
    if ( !db.isValid() )
    {
        qWarning("Error: db is not valid.");
        return;
    }

    Docmanager *dm = NULL;
    if ( !m__Docmanagers.contains( db.connectionName() ) )
    {
        dm = new Docmanager( db );
        m__Docmanagers.insert( db.connectionName(), dm );
    }
    else dm = m__Docmanagers[db.connectionName()];

    dm->setDeclar( declarId );
    if ( docIndex < 0 || docIndex >= dm->declarDocuments()->rowCount() ) return;

    MFCDocument *doc = dm->declarDocument( dm->declarDocuments()->index( docIndex, 0 ) );
    if ( !dm->loadDocument( doc ) )
    {
        qWarning("Error: while loading document.");
        return;
    }
}

QMLDocumentLoader_P::QMLDocumentLoader_P() :
    QObject(NULL),
    m__Documents(QList<QString>()),
    m__Docmanagers(QHash<QString, Docmanager *>())
{
}
