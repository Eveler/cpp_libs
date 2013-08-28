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

bool QMLDocument::isValid() const
{
    return (source() != QUuid().toString() );
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

