#include "menu_perioddates.h"

#include "menu_perioddatesprivate.h"

#include <QToolTip>


Menu_PeriodDates::Menu_PeriodDates(QWidget *parent) :
  QMenu(parent),
  m__P(new Menu_PeriodDatesPrivate( this ))
{
}

Menu_PeriodDates::~Menu_PeriodDates()
{
  delete m__P;
}

const QDate & Menu_PeriodDates::firstDate() const
{
  return m__P->m__FirstDate;
}

const QDate & Menu_PeriodDates::lastDate() const
{
  return m__P->m__LastDate;
}

void Menu_PeriodDates::setCurrentDateIcon( const QIcon &icon )
{
  m__P->m__Icon = icon;
  foreach ( QAction *action, actions() )
    periodByAction( action );
}

void Menu_PeriodDates::setPeriodEnabled( Period period, bool enabled )
{
  switch ( period )
  {
  case Daily:
    m__P->m__Daily->setEnabled( enabled );
    break;
  case Weekly:
    m__P->m__Weekly->setEnabled( enabled );
    break;
  case Monthly:
    m__P->m__Monthly->setEnabled( enabled );
    break;
  case Quarterly:
    m__P->m__Quarterly->setEnabled( enabled );
    break;
  case Semiannual:
    m__P->m__Semiannual->setEnabled( enabled );
    break;
  case Yearly:
    m__P->m__Yearly->setEnabled( enabled );
    break;
  }
}

QPair<QDate, QDate> Menu_PeriodDates::periodByAction( QAction *action )
{
  QPair<QDate, QDate> result = QPair<QDate, QDate>();

  if ( action == m__P->m__Daily->actions().value( 0, NULL ) )
  {
    result.first = QDate::currentDate();
    result.second = result.first;
  }
  else if ( action == m__P->m__Daily->actions().value( 1, NULL ) )
  {
    result.first = QDate::currentDate().addDays( -1 );
    result.second = result.first;
  }
  else if ( action == m__P->m__Daily->actions().value( 2, NULL ) )
  {
    result.first = QDate::currentDate().addDays( -2 );
    result.second = result.first;
  }
  else if ( action == m__P->m__Weekly->actions().value( 0, NULL ) )
  {
    result.first = QDate::currentDate().addDays( -7*0 ).addDays( (QDate::currentDate().dayOfWeek()-1)*-1 );
    result.second = QDate::currentDate().addDays( -7*0 ).addDays( 7-QDate::currentDate().dayOfWeek() );
  }
  else if ( action == m__P->m__Weekly->actions().value( 1, NULL ) )
  {
    result.first = QDate::currentDate().addDays( -7*1 ).addDays( (QDate::currentDate().dayOfWeek()-1)*-1 );
    result.second = QDate::currentDate().addDays( -7*1 ).addDays( 7-QDate::currentDate().dayOfWeek() );
  }
  else if ( action == m__P->m__Weekly->actions().value( 2, NULL ) )
  {
    result.first = QDate::currentDate().addDays( -7*2 ).addDays( (QDate::currentDate().dayOfWeek()-1)*-1 );
    result.second = QDate::currentDate().addDays( -7*2 ).addDays( 7-QDate::currentDate().dayOfWeek() );
  }
  else if ( action == m__P->m__Monthly->actions().value( 0, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), QDate::currentDate().month(), 1 );
    result.second = QDate( QDate::currentDate().year(), QDate::currentDate().month(),
                           QDate::currentDate().daysInMonth() );
  }
  else if ( action == m__P->m__Monthly->actions().value( 1, NULL ) )
  {
    QDate buf = QDate( QDate::currentDate().year(), QDate::currentDate().month(), 1 );
    buf = buf.addDays( -1 );
    result.first = QDate( buf.year(), buf.month(), 1 );
    result.second = QDate( buf.year(), buf.month(), buf.daysInMonth() );
  }
  else if ( action == m__P->m__Monthly->actions().value( 2, NULL ) )
  {
    QDate buf = QDate( QDate::currentDate().year(), QDate::currentDate().month(), 1 );
    buf = buf.addDays( -1 );
    buf = QDate( buf.year(), buf.month(), 1 );
    buf = buf.addDays( -1 );
    result.first = QDate( buf.year(), buf.month(), 1 );
    result.second = QDate( buf.year(), buf.month(), buf.daysInMonth() );
  }
  else if ( action == m__P->m__Quarterly->actions().value( 0, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 1, 1 );
    result.second = QDate( QDate::currentDate().year(), 3, 1 );
    result.second = QDate( QDate::currentDate().year(), 3, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Quarterly->actions().value( 1, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 4, 1 );
    result.second = QDate( QDate::currentDate().year(), 6, 1 );
    result.second = QDate( QDate::currentDate().year(), 6, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Quarterly->actions().value( 2, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 7, 1 );
    result.second = QDate( QDate::currentDate().year(), 9, 1 );
    result.second = QDate( QDate::currentDate().year(), 9, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Quarterly->actions().value( 3, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 10, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Semiannual->actions().value( 0, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 1, 1 );
    result.second = QDate( QDate::currentDate().year(), 6, 1 );
    result.second = QDate( QDate::currentDate().year(), 6, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Semiannual->actions().value( 1, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 7, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, result.second.daysInMonth() );

    if ( QDate::currentDate() >= result.first && QDate::currentDate() <= result.second )
      action->setIcon( m__P->m__Icon );
    else action->setIcon( QIcon() );
  }
  else if ( action == m__P->m__Yearly->actions().value( 0, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year(), 1, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, 1 );
    result.second = QDate( QDate::currentDate().year(), 12, result.second.daysInMonth() );
  }
  else if ( action == m__P->m__Yearly->actions().value( 1, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year()-1, 1, 1 );
    result.second = QDate( QDate::currentDate().year()-1, 12, 1 );
    result.second = QDate( QDate::currentDate().year()-1, 12, result.second.daysInMonth() );
  }
  else if ( action == m__P->m__Yearly->actions().value( 2, NULL ) )
  {
    result.first = QDate( QDate::currentDate().year()-2, 1, 1 );
    result.second = QDate( QDate::currentDate().year()-2, 12, 1 );
    result.second = QDate( QDate::currentDate().year()-2, 12, result.second.daysInMonth() );
  }

  return result;
}

void Menu_PeriodDates::actionHovered( QAction *action )
{
  QPair<QDate, QDate> result = periodByAction( action );
  if ( result.first == result.second )
  {
    QPoint p = cursor().pos();
    p.setY( p.y()+cursor().pixmap().height() );
    QToolTip::showText( cursor().pos(), tr( "%1" ).arg(
                          result.first.toString( "dd.MM.yyyy" ) ) );
  }
  else
  {
    QPoint p = cursor().pos();
    p.setY( p.y()+cursor().pixmap().height() );
    QToolTip::showText( cursor().pos(), tr( "%1 - %2" ).arg(
                          result.first.toString( "dd.MM.yyyy" ),
                          result.second.toString( "dd.MM.yyyy" ) ) );
  }
  emit periodHovered( result.first, result.second );
}

void Menu_PeriodDates::actionTriggered( QAction *action )
{
  QPair<QDate, QDate> result = periodByAction( action );
  m__P->m__FirstDate = result.first;
  m__P->m__LastDate = result.second;
  emit periodChanged( result.first, result.second );
}
