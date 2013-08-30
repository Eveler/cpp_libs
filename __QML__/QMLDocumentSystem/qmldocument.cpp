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

void QMLDocument::reset()
{
    if ( p->m__Source == NULL ) return;

    int addedCount = p->m__AddedPages.count();
    foreach (MFCDocumentPage *page, p->m__AddedPages)
        for ( int index = p->m__Source->pages()->count()-1; index > -1; index-- )
            if ( p->m__Source->pages()->getPage( index ) == page )
            {
                p->m__AddedPages.removeOne( page );
                p->m__Source->pages()->removePage( index );
                index = p->m__Source->pages()->count();
                emit pageRemoved( index );
            }
    if ( addedCount > 0 ) emit pagesCountChanged();
}

void QMLDocument::configureScanner()
{
    if ( p->m__Source == NULL ) return;

    p->configureScanner();
}

void QMLDocument::addPage()
{
    if ( p->m__Source == NULL ) return;

    p->m__ReplacePage = -1;
    p->doScan();
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

