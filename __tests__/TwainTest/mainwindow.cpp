#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "amslogger.h"
#include <QUuid>

int scanned_page_c = 0;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_pTwain(NULL)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::nativeEvent( const QByteArray &eventType, void *message, long *result )
{
  Q_UNUSED(eventType);
  return winEvent( (MSG*)message, result );
}

bool MainWindow::winEvent( MSG *message, long */*result*/ )
{
  if ( m_pTwain != NULL )
    m_pTwain->processMessage(*message);
  return false;
}

void MainWindow::on_pushButton_clicked()
{
  releaseTWAIN();
  initTWAIN();
  m_pTwain->acquire();
}

void MainWindow::pixmapAcquired(QPixmap *pix)
{
  pix->save(QUuid::createUuid().toString()+".png");
  scanned_page_c++;
  LogDebug()<<Q_FUNC_INFO<<scanned_page_c;
  delete pix;
}

void MainWindow::on_pushButton_2_clicked()
{
  releaseTWAIN();
  initTWAIN();
  m_pTwain->selectSource();
}

void MainWindow::initTWAIN()
{
  scanned_page_c = 0;
    m_pTwain = new QTwain( NULL );
    m_pTwain->setParent( this );
    m_pTwain->setEmitPixmaps();
    QObject::connect( m_pTwain, SIGNAL(pixmapAcquired(QPixmap*)),
                      SLOT(pixmapAcquired(QPixmap*)) );
}

void MainWindow::releaseTWAIN()
{
    if ( m_pTwain != NULL )
    {
        delete m_pTwain;
        m_pTwain = NULL;
    }
}
