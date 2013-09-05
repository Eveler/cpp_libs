#include "qmldocumentloader.h"

#include "docmanager.h"

#include <QSqlDatabase>


QMLDocumentLoader::QMLDocumentLoader(QQuickItem *parent) :
    QQuickItem(parent),
    m__ConnectionName(QString()),
    m__Docmanager(NULL),
    m__DeclarId(-1),
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
    m__Docmanager->setDeclar( -1 );
}

int QMLDocumentLoader::declar() const
{
    return m__DeclarId;
}

void QMLDocumentLoader::setDeclar( int declarId )
{
    if ( m__Docmanager == NULL ) connectionName();
    int oldCount = count();
    m__Docmanager->unsetDeclar();
    m__Docmanager->setDeclar( declarId );
    if ( m__DeclarId != declarId )
    {
        m__DeclarId = declarId;
        emit declarChanged();
        emit countChanged();
    }
    if ( oldCount != count() )
        emit countChanged();
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

QString QMLDocumentLoader::document( int index )
{
    if ( index < 0 || index >= m__Docmanager->declarDocuments()->documents().count() )
        return QUuid::createUuid().toString();

    MFCDocument *doc = m__Docmanager->declarDocuments()->documents()[index];
    m__Docmanager->loadDocument( doc );
    return doc->uuid().toString();
}

bool QMLDocumentLoader::save()
{
    if ( m__Docmanager == NULL ) return false;

    if ( !m__Docmanager->saveDocuments() ) return false;
    return m__Docmanager->saveDeleteDocuments();
}

void QMLDocumentLoader::dataTransferProgress( qint64 current,qint64 total )
{
    m__DataTransferProgress = (int)((qreal)current/(qreal)total*100.);
    emit progressChanged();
}
