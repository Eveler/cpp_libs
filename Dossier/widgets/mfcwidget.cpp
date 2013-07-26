#include "mfcwidget.h"
#include <QEvent>
#include <QCloseEvent>
//#include "macros.h"

MFCWidget::MFCWidget(QWidget *parent) :
    QWidget(parent),
    m__CanClose( true )
{
}

bool MFCWidget::canClose() const
{
  return m__CanClose;
}

void MFCWidget::changeWindowState( Qt::WindowState wState )
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

void MFCWidget::setCanClose( bool can )
{
  m__CanClose = can;
}

void MFCWidget::changeEvent( QEvent *e )
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

  QWidget::changeEvent( e );
}

void MFCWidget::closeEvent( QCloseEvent *e )
{
  if ( !m__CanClose ) e->ignore();
  else e->accept();
}
