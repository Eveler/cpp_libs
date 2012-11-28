#include "mfcmainwindow.h"
#include <QEvent>
#include "macros.h"

MFCMainWindow::MFCMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
}

void MFCMainWindow::changeWindowState( Qt::WindowState wState )
{
  if ( wState == Qt::WindowMinimized &&
       windowFlags().testFlag( Qt::WindowMinimizeButtonHint ) )
    this->showMinimized();
  else if ( wState == Qt::WindowFullScreen )
    this->showFullScreen();
  else if ( wState == Qt::WindowMaximized &&
            windowFlags().testFlag( Qt::WindowMaximizeButtonHint ) )
    this->showMaximized();
  else
    this->showNormal();
}

void MFCMainWindow::changeEvent( QEvent *e )
{
  if ( e->type() == QEvent::WindowStateChange )
  {
    if ( isMinimized() )
      emit windowStateChanged( Qt::WindowMinimized );
    else if ( isFullScreen() )
      emit windowStateChanged( Qt::WindowFullScreen );
    else if ( isMaximized() )
      emit windowStateChanged( Qt::WindowMaximized );
    else
      emit windowStateChanged( Qt::WindowNoState );
  }

  QMainWindow::changeEvent( e );
}
