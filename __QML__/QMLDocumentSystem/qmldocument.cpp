#include "qmldocument.h"

#include "qmldocument_p.h"


QMLDocument::QMLDocument(QQuickItem *parent):
    QQuickItem(parent)
{

    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new QMLDocument_P( this );
    connect( p, SIGNAL(pagesCountChanged()), SIGNAL(pagesCountChanged()) );
    connect( p, SIGNAL(pageAdded(int)), SIGNAL(pageAdded(int)) );
    connect( p, SIGNAL(pageRemoved(int)), SIGNAL(pageRemoved(int)) );
}

QString QMLDocument::source() const
{
    if ( p->m__Source == NULL ) return QUuid().toString();
    return p->m__Source->uuid().toString();
}

void QMLDocument::setSource( QString source )
{
    MFCDocument *oldDocument = p->m__Source;
    if ( p->m__Source != NULL )
    {
        disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(documentRemoved()) );
        disconnect( p->m__Source->pages(), SIGNAL(countChanged(int)),
                    this, SIGNAL(pagesCountChanged()) );
        disconnect( p->m__Source->attachments(), SIGNAL(countChanged(int)),
                    this, SIGNAL(attachmentsCountChanged()) );
        disconnect( p->m__Source, SIGNAL(type_Changed()), this, SIGNAL(typeChanged()) );
        disconnect( p->m__Source, SIGNAL(name_Changed()), this, SIGNAL(nameChanged()) );
        disconnect( p->m__Source, SIGNAL(series_Changed()), this, SIGNAL(seriesChanged()) );
        disconnect( p->m__Source, SIGNAL(number_Changed()), this, SIGNAL(numberChanged()) );
        disconnect( p->m__Source, SIGNAL(date_Changed()), this, SIGNAL(docdateChanged()) );
        disconnect( p->m__Source, SIGNAL(expiresDate_Changed()),
                    this, SIGNAL(docexpiresChanged()) );
        p->m__Source = NULL;
    }
    MFCDocument *document = MFCDocument::document( QUuid( source ) );
    p->m__Source = document;
    if (  p->m__Source != NULL )
    {
        connect( p->m__Source, SIGNAL(destroyed()), SLOT(documentRemoved()) );
        connect( p->m__Source->pages(), SIGNAL(countChanged(int)),
                 SIGNAL(pagesCountChanged()) );
        connect( p->m__Source->attachments(), SIGNAL(countChanged(int)),
                 SIGNAL(attachmentsCountChanged()) );
        connect( p->m__Source, SIGNAL(type_Changed()), SIGNAL(typeChanged()) );
        connect( p->m__Source, SIGNAL(name_Changed()), SIGNAL(nameChanged()) );
        connect( p->m__Source, SIGNAL(series_Changed()), SIGNAL(seriesChanged()) );
        connect( p->m__Source, SIGNAL(number_Changed()), SIGNAL(numberChanged()) );
        connect( p->m__Source, SIGNAL(date_Changed()), SIGNAL(docdateChanged()) );
        connect( p->m__Source, SIGNAL(expiresDate_Changed()), SIGNAL(docexpiresChanged()) );
    }
    if ( oldDocument != p->m__Source )
    {
        emit sourceChanged();
        emit pagesCountChanged();
        emit attachmentsCountChanged();
    }
}

int QMLDocument::pagesCount() const
{
    if ( p->m__Source == NULL ) return 0;
    return p->m__Source->pages()->count();
}

QString QMLDocument::page( int index )
{
    if ( index < 0 || index >= pagesCount() ) return QString();

    return tr( "image://qmldocumentprovider/%1/%2" ).arg( source() ).arg( index );
}

int QMLDocument::attachmentsCount() const
{
    if ( p->m__Source == NULL ) return 0;
    return p->m__Source->attachments()->count();
}

QString QMLDocument::attachmentName( int index )
{
    if ( index < 0 || index >= pagesCount() ) return QString();

    return p->m__Source->attachments()->getAttachment( index ).fileName();
}

bool QMLDocument::openAttachment( int index )
{
    if ( index < 0 || index >= pagesCount() ) return false;

    return true;
}

bool QMLDocument::isValid() const
{
    return (source() != QUuid().toString() );
}

void QMLDocument::resetContent()
{
    if ( p->m__Source == NULL ) return;

    int addedPagesCount = p->m__AddedPages.count();
    foreach (MFCDocumentPage *page, p->m__AddedPages)
        for ( int index = p->m__Source->pages()->count()-1; index > -1; index-- )
            if ( p->m__Source->pages()->getPage( index ) == page )
            {
                p->m__AddedPages.removeOne( page );
                p->m__Source->pages()->removePage( index );
                index = p->m__Source->pages()->count();
                emit pageRemoved( index );
            }
    if ( addedPagesCount > 0 ) emit pagesCountChanged();
}

void QMLDocument::configureScanner()
{
    if ( p->m__Source == NULL ) return;

    p->configureScanner();
}

void QMLDocument::scanPage()
{
    if ( p->m__Source == NULL ) return;

    p->m__ReplacePage = -1;
    p->doScan();
}

void QMLDocument::addPage( QUrl path )
{
//    qWarning() << path.isValid() << path;
    if ( p->m__Source == NULL || !path.isValid() ) return;

    p->m__ReplacePage = -1;
    p->fromFile( path.toLocalFile() );
}

bool QMLDocument::removablePage( int index )
{
    if ( p->m__Source == NULL
         || index < 0 || index >= p->m__Source->pages()->count() )
        return false;

    MFCDocumentPage *page = p->m__Source->pages()->getPage( index );
    return p->m__AddedPages.contains( page );
}

void QMLDocument::removePage( int index )
{
    if ( p->m__Source == NULL
         || index < 0 || index >= p->m__Source->pages()->count() )
        return;

    MFCDocumentPage *page = p->m__Source->pages()->getPage( index );
    if ( !p->m__AddedPages.contains( page ) ) return;

    p->m__AddedPages.removeOne( page );
    p->m__Source->pages()->removePage( index );
    emit pageRemoved( index );
}

QString QMLDocument::type() const
{
    if ( p->m__Source == NULL ) return QString();

    return p->m__Source->type();
}

void QMLDocument::setType( const QString &type )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setType( type );
}

QString QMLDocument::name() const
{
    if ( p->m__Source == NULL ) return QString();

    return p->m__Source->name();
}

void QMLDocument::setName( const QString &name )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setName( name );
}

QString QMLDocument::series() const
{
    if ( p->m__Source == NULL ) return QString();

    return p->m__Source->series();
}

void QMLDocument::setSeries( const QString &series )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setSeries( series );
}

QString QMLDocument::number() const
{
    if ( p->m__Source == NULL ) return QString();

    return p->m__Source->number();
}

void QMLDocument::setNumber( const QString &number )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setNumber( number );
}

QDate QMLDocument::docdate() const
{
    if ( p->m__Source == NULL ) return QDate();

    return p->m__Source->date();
}

void QMLDocument::setDocdate( const QDate &docdate )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setDate( docdate );
}

QDate QMLDocument::docexpires() const
{
    if ( p->m__Source == NULL ) return QDate();

    return p->m__Source->expiresDate();
}

void QMLDocument::setDocexpires( const QDate &docexpires )
{
    if ( p->m__Source == NULL ) return;

    return p->m__Source->setExpiresDate( docexpires );
}

QMLDocument::~QMLDocument()
{
    delete p;
    p = NULL;
}

void QMLDocument::documentRemoved()
{
    setSource( QString() );
}

