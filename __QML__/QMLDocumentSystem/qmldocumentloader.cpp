#include "qmldocumentloader.h"

#include "docmanager.h"

#include <QSqlDatabase>


QMLDocumentLoader::QMLDocumentLoader(QQuickItem *parent) :
    QQuickItem(parent),
    m__ConnectionName(QString()),
    m__Docmanager(NULL),
    m__DataTransferProgress(0)
{
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
    {
        m__ConnectionName = connectionName;
        delete m__Docmanager;
        m__Docmanager = NULL;
    }
    else m__ConnectionName = QSqlDatabase::database(
                QLatin1String( QSqlDatabase::defaultConnection ), false ).connectionName();
    QSqlDatabase db = QSqlDatabase::database( m__ConnectionName );
    m__Docmanager = new Docmanager( db, this );
    connect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
             SLOT(dataTransferProgress(qint64,qint64)) );
    emit connectionNameChanged();
    m__DataTransferProgress = 0;
    loadDocuments( -1 );
}

int QMLDocumentLoader::count()
{
    if ( m__Docmanager == NULL ) connectionName();
    return m__Docmanager->declarDocuments()->documents().count();
}

int QMLDocumentLoader::progress() const
{
    return m__DataTransferProgress;
}

void QMLDocumentLoader::loadDocuments( int declarId )
{
    if ( m__Docmanager == NULL ) connectionName();
    m__Docmanager->unsetDeclar();
    m__Docmanager->setDeclar( declarId );
    emit countChanged();
}

QString QMLDocumentLoader::document( int index )
{
    if ( index < 0 || index >= m__Docmanager->declarDocuments()->documents().count() )
        return QUuid::createUuid().toString();

    MFCDocument *doc = m__Docmanager->declarDocuments()->documents()[index];
    if ( !m__Docmanager->loadDocument( doc ) )
        qWarning( "Warning: document not loaded!" );
//    if ( !m__Docmanager->loadDocument( doc ) )
//    {
//        qWarning( "Error: while loading document!" );
//        return QUuid::createUuid().toString();
//    }
    return doc->uuid().toString();
}

void QMLDocumentLoader::dataTransferProgress( qint64 current,qint64 total )
{
    m__DataTransferProgress = (int)((qreal)current/(qreal)total*100.);
    emit progressChanged();
}
