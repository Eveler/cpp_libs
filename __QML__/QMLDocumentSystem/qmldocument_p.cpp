#include "qmldocument_p.h"

#include <QMessageBox>
#include <QApplication>


#define SCANAPP_PATH qApp->applicationDirPath()+"/MFCScanProject.exe"

QMLDocument_P::QMLDocument_P(QMLDocument *parent) :
    QObject(parent),
    m__Source(NULL),
    m__AddedPages(QList<MFCDocumentPage *>()),
    m__ReplacePage(-1)
{
#ifdef Q_OS_WIN
    scanProcess = new QProcess( this );
//    connect( scanProcess, SIGNAL(started()),
//             SLOT(scanProcessStarted()) );
//    connect( scanProcess, SIGNAL(error(QProcess::ProcessError)),
//             SLOT(scanProcessError(QProcess::ProcessError)) );
    connect( scanProcess, SIGNAL(readyReadStandardOutput()),
             SLOT(readyReadScanProcessOutput()) );
#endif
}

QMLDocument_P::~QMLDocument_P()
{
#ifdef Q_OS_WIN
    if( scanProcess->pid() != 0 ) scanProcess->kill();
    delete scanProcess;
    scanProcess = NULL;
#endif
}

QMLDocument * QMLDocument_P::p_dptr() const
{
    return qobject_cast<QMLDocument *>( parent() );
}

void QMLDocument_P::configureScanner()
{
#ifdef Q_OS_WIN
    if( scanProcess->pid() != 0 ) scanProcess->kill();
    QString command = tr( "%1 -select_source" ).arg( SCANAPP_PATH );
    qWarning() << command;
    scanProcess->start( command );
    scanProcess->waitForStarted();
#endif
}

void QMLDocument_P::doScan()
{
#ifdef Q_OS_WIN
    if( scanProcess->pid() != 0 ) scanProcess->kill();
    QString command = tr( "%1 -scan" ).arg( SCANAPP_PATH );
    qWarning() << command;
    scanProcess->start( tr( "%1 -scan" ).arg( SCANAPP_PATH ) );
    scanProcess->waitForStarted();
#endif
}

#ifdef Q_OS_WIN
//void QMLDocument_P::scanProcessStarted()
//{
//    qWarning() << "scanProcessStarted";
//}

//void QMLDocument_P::scanProcessError( QProcess::ProcessError processError )
//{
//    qWarning() << "scanProcessError" << processError;
//}

void QMLDocument_P::readyReadScanProcessOutput()
{
    QString result = QVariant( scanProcess->readAllStandardOutput() ).toString();
    if ( result.contains( tr( "select_source: fail" ) ) )
        QMessageBox::warning( NULL, tr( "Выбор устройства" ),
                              tr( "Не удалось выбрать устройство сканирования!" ) );
    else if ( result.contains( tr( "scan: fail" ) ) )
        QMessageBox::warning( NULL, tr( "Сканирование" ),
                              tr( "Не удалось сканировать документ!" ) );
    else if ( result.contains( tr( "scan: success" ) ) )
    {
        result = result.remove( 0, result.indexOf( tr( "scan: success" ) )+
                                tr( "scan: success | " ).length() );
        QPixmap pixmap;
        if(pixmap.load(result,"PNG"))
        {
            if( pixmap.width() > 1700 )
                pixmap = pixmap.scaledToWidth( 1700, Qt::SmoothTransformation );
            if( pixmap.height() > 2338 )
                pixmap = pixmap.scaledToHeight( 2338, Qt::SmoothTransformation );

            if ( m__ReplacePage == -1 )
            {
                int pageNum = m__Source->pages()->count()+1;
                MFCDocumentPage *page = new MFCDocumentPage(
                            tr( "Страница %1 (Скан %1)" ).arg( pageNum ), pixmap );
                m__Source->addPage( *page );
                m__AddedPages << page;
                emit pageAdded( pageNum-1 );
                emit pagesCountChanged();
            }
            //            else
            //            {
            //                MFCDocumentPage *page=new MFCDocumentPage(
            //                      m__Source->pages()->getPage( m__ReplacePage )->getPageName(), pixmap );
            //                m__AddedPages.replace(
            //                            m__AddedPages.indexOf(
            //                                m__Source->pages()->getPage( m__ReplacePage ) ), page );
            //                m__Source->replacePage( m__ReplacePage, *page );
            //                emit pageAdded( m__ReplacePage );
            //                emit pagesCountChanged();
            //            }
        }
        else QMessageBox::warning( NULL, "Ошибка", "Не удалось получить изображение!" );
        if ( QFile( result ).exists() ) QFile( result ).remove();
    }
}
#endif
