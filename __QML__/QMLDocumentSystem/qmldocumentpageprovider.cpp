#include "qmldocumentpageprovider.h"

#include "mfcdocument.h"

#include <QUuid>


QMLDocumentPageProvider::QMLDocumentPageProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap QMLDocumentPageProvider::requestPixmap(
        const QString &id, QSize *size, const QSize &requestedSize )
{
    int width = 100;
    int height = 50;

    QPixmap nullPixmap( requestedSize.width() > 0 ? requestedSize.width() : width,
                        requestedSize.height() > 0 ? requestedSize.height() : height);
    nullPixmap.fill( QColor( 0, 0, 0, 0 ) );

    bool ok = false;
    QStringList idList = id.split( "/" );
    QString uuid( idList.first() );
    MFCDocument *doc = MFCDocument::document( uuid );
    if ( idList.count() != 2 || uuid.isNull() || doc == NULL )
    {
        qWarning() << "QMLDocumentPageProvider error! Level 1:" <<
                      "\nidList.count" << idList.count() <<
                      "\nuuid.isNull" << uuid.isNull() <<
                      "\ndoc" << doc;
        if ( size != NULL ) *size = nullPixmap.size();
        return nullPixmap;
    }

    int index = idList.last().toInt( &ok );
    if ( !ok || index < 0 || index >= doc->pages()->count() )
    {
        qWarning() << "QMLDocumentPageProvider error! Level 2:" <<
                      "\ntry get page index" << ok <<
                      "\nindex < 0" << (index < 0) <<
                      "\nindex >= doc->pages()->count()" << (index >= doc->pages()->count()) <<
                      "\nindex" << index;
        if ( size != NULL ) *size = nullPixmap.size();
        return nullPixmap;
    }

    QPixmap pixmap;
    pixmap.loadFromData( doc->pages()->getPage( index )->getBody() );
    if ( size != NULL ) *size = pixmap.size();

//        QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
//                       requestedSize.height() > 0 ? requestedSize.height() : height);
//        pixmap.fill(QColor(id).rgba());

    return pixmap;
}
