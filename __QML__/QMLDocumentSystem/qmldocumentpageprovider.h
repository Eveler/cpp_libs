#ifndef QMLDOCUMENTPAGEPROVIDER_H
#define QMLDOCUMENTPAGEPROVIDER_H

#include <QQuickImageProvider>

#include <QDebug>


class QMLDocumentPageProvider : public QQuickImageProvider
{
public:
    QMLDocumentPageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // QMLDOCUMENTPAGEPROVIDER_H
