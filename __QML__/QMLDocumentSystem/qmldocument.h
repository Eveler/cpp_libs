#ifndef QMLDOCUMENT_H
#define QMLDOCUMENT_H

#include <QQuickItem>

#include "docmanager.h"


class QMLDocument_P;

class QMLDocument : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QMLDocument)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int pagesCount READ pagesCount NOTIFY pagesCountChanged)

public:
    QMLDocument(QQuickItem *parent = 0);
    ~QMLDocument();

    QString source() const;
    void setSource( QString source );

    int pagesCount();


signals:
    void sourceChanged();
    void pagesCountChanged();


private:
    QMLDocument_P *p;

private slots:
    void documentRemoved();
};

QML_DECLARE_TYPE(QMLDocument)

#endif // QMLDOCUMENT_H

