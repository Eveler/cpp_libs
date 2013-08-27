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
}

QString QMLDocument::source() const
{
    return p->m__Source->uuid().toString();
}

void QMLDocument::setSource( QString source )
{
    int oldPagesCount = 0;
    if ( p->m__Source != NULL )
    {
        disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(documentRemoved()) );
        disconnect( p->m__Source->pages(), SIGNAL(countChanged(int)),
                    this, SIGNAL(pagesCountChanged()) );
        oldPagesCount = pagesCount();
        p->m__Source = NULL;
    }
    MFCDocument *document = MFCDocument::document( QUuid( source ) );
    p->m__Source = document;
    if (  p->m__Source != NULL )
    {
        connect( p->m__Source, SIGNAL(destroyed()), SLOT(documentRemoved()) );
        connect( p->m__Source->pages(), SIGNAL(countChanged(int)), SIGNAL(pagesCountChanged()) );
    }
    if ( oldPagesCount != pagesCount() ) emit pagesCountChanged();
    emit sourceChanged();
}

int QMLDocument::pagesCount()
{
    if ( p->m__Source == NULL ) return 0;
    return p->m__Source->pages()->count();
}

QString QMLDocument::page( int index )
{
    if ( index < 0 || index >= pagesCount() ) return QString();

    return tr( "image://qmldocumentprovider/%1/%2" ).arg( source() ).arg( index );
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

