#include "qmldocumentloader.h"

#include "qmldocumentloader_p.h"

#include <QSqlDatabase>


QMLDocumentLoader::QMLDocumentLoader(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = QMLDocumentLoader_P::instance();
    connect( p, SIGNAL(documentsChanged()), SIGNAL(documentsChanged()) );
}

QString QMLDocumentLoader::connectionName()
{
    if ( !QSqlDatabase::connectionNames().contains( m__ConnectionName ) )
        setConnectionName( QString() );
    return m__ConnectionName;
}
void QMLDocumentLoader::setConnectionName( QString connectionName )
{
    m__ConnectionName = QString();
    if ( QSqlDatabase::connectionNames().contains( connectionName ) )
        m__ConnectionName = connectionName;
    else m__ConnectionName = QSqlDatabase::database(
                QLatin1String( QSqlDatabase::defaultConnection ), false ).connectionName();
    emit connectionNameChanged();
}

const QList<QString> & QMLDocumentLoader::documents() const
{
    return p->documents();
}

void QMLDocumentLoader::setDeclar( int delcarId )
{
    p->loadDocument( delcarId, -1, connectionName() );
}

void QMLDocumentLoader::loadDocument( int docIndex )
{
    p->loadDocument( delcarId, docIndex, connectionName() );
}
