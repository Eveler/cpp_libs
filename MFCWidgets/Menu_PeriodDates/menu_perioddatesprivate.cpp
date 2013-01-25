#include "menu_perioddatesprivate.h"

#include "menu_perioddates.h"


Menu_PeriodDatesPrivate::Menu_PeriodDatesPrivate( Menu_PeriodDates *parent ) :
  m__FirstDate(QDate()),
  m__LastDate(QDate()),
  m__Icon(QIcon())
{
  m__Separators = QList<QAction *>();

  m__Daily = new QActionGroup( parent );
  m__Daily->addAction( parent->addAction( QObject::tr( "Сегодня" ) ) );
  m__Daily->addAction( parent->addAction( QObject::tr( "Вчера" ) ) );
  m__Daily->addAction( parent->addAction( QObject::tr( "Позавчера" ) ) );

  m__Separators << parent->addSeparator();

  m__Weekly = new QActionGroup( parent );
  m__Weekly->addAction( parent->addAction( QObject::tr( "Эта неделя" ) ) );
  m__Weekly->addAction( parent->addAction( QObject::tr( "Прошлая неделя" ) ) );
  m__Weekly->addAction( parent->addAction( QObject::tr( "Позапрошлая неделя" ) ) );

  m__Separators << parent->addSeparator();

  m__Monthly = new QActionGroup( parent );
  m__Monthly->addAction( parent->addAction( QObject::tr( "Этот месяц" ) ) );
  m__Monthly->addAction( parent->addAction( QObject::tr( "Прошлый месяц" ) ) );
  m__Monthly->addAction( parent->addAction( QObject::tr( "Позапрошлый месяц" ) ) );

  m__Separators << parent->addSeparator();

  m__Quarterly = new QActionGroup( parent );
  m__Quarterly->addAction( parent->addAction( QObject::tr( "Первый квартал" ) ) );
  m__Quarterly->addAction( parent->addAction( QObject::tr( "Второй квартал" ) ) );
  m__Quarterly->addAction( parent->addAction( QObject::tr( "Третий квартал" ) ) );
  m__Quarterly->addAction( parent->addAction( QObject::tr( "Четвертый квартал" ) ) );

  m__Separators << parent->addSeparator();

  m__Semiannual = new QActionGroup( parent );
  m__Semiannual->addAction( parent->addAction( QObject::tr( "Первое полугодие" ) ) );
  m__Semiannual->addAction( parent->addAction( QObject::tr( "Второе полугодие" ) ) );

  m__Separators << parent->addSeparator();

  m__Yearly = new QActionGroup( parent );
  m__Yearly->addAction( parent->addAction( QObject::tr( "Этот год" ) ) );
  m__Yearly->addAction( parent->addAction( QObject::tr( "Прошлый год" ) ) );
  m__Yearly->addAction( parent->addAction( QObject::tr( "Позапрошлый год" ) ) );

  QObject::connect( parent, SIGNAL(hovered(QAction*)), parent, SLOT(actionHovered(QAction*)) );
  QObject::connect( parent, SIGNAL(triggered(QAction*)), parent, SLOT(actionTriggered(QAction*)) );
}

Menu_PeriodDatesPrivate::~Menu_PeriodDatesPrivate()
{
}
