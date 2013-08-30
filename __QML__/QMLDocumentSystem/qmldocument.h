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
    Q_PROPERTY(int attachmentsCount READ attachmentsCount NOTIFY attachmentsCountChanged)

public:
    QMLDocument(QQuickItem *parent = 0);
    ~QMLDocument();

    QString source() const;
    void setSource( QString source );

    int pagesCount() const;
    Q_INVOKABLE QString page( int index );

    int attachmentsCount() const;
    Q_INVOKABLE QString attachmentName( int index );
    Q_INVOKABLE bool openAttachment( int index );

    Q_INVOKABLE bool isValid() const;

    Q_INVOKABLE void reset();

    Q_INVOKABLE void configureScanner();
    Q_INVOKABLE void addPage();


signals:
    void sourceChanged();
    void pagesCountChanged();
    void pageAdded( int index );
    void pageRemoved( int index );
    void attachmentsCountChanged();


private:
    QMLDocument_P *p;

private slots:
    void documentRemoved();
};

QML_DECLARE_TYPE(QMLDocument)

#endif // QMLDOCUMENT_H

