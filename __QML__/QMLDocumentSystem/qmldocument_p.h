#ifndef QMLDOCUMENT_P_H
#define QMLDOCUMENT_P_H

#include "qmldocument.h"

#include <QProcess>


class QMLDocument_P : public QObject
{
    Q_OBJECT
    friend class QMLDocument;

public:


signals:
    void pagesCountChanged();
    void pageAdded( int index );
    void pageRemoved( int index );


public slots:


private:
    MFCDocument *m__Source;
    QList<MFCDocumentPage *> m__AddedPages;
    int m__ReplacePage;
#ifdef Q_OS_WIN
    QProcess *scanProcess;
#endif

    explicit QMLDocument_P(QMLDocument *parent);
    ~QMLDocument_P();

    QMLDocument * p_dptr() const;

    void configureScanner();
    void doScan();
    void fromFile( QString path );


private slots:
#ifdef Q_OS_WIN
//    void scanProcessStarted();
//    void scanProcessError(QProcess::ProcessError);
    void readyReadScanProcessOutput();
#endif
};

#endif // QMLDOCUMENT_P_H
