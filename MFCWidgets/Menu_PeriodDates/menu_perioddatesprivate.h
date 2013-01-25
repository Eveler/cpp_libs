#ifndef MENU_PERIODDATESPRIVATE_H
#define MENU_PERIODDATESPRIVATE_H

#include <QActionGroup>

#include <QDate>
#include <QIcon>


class Menu_PeriodDates;

class Menu_PeriodDatesPrivate
{
  friend class Menu_PeriodDates;
public:
  Menu_PeriodDatesPrivate( Menu_PeriodDates *parent );
  ~Menu_PeriodDatesPrivate();

private:
  QActionGroup *m__Daily;
  QActionGroup *m__Weekly;
  QActionGroup *m__Monthly;
  QActionGroup *m__Quarterly;
  QActionGroup *m__Semiannual;
  QActionGroup *m__Yearly;

  QList<QAction *> m__Separators;

  QDate m__FirstDate;
  QDate m__LastDate;

  QIcon m__Icon;
};

#endif // MENU_PERIODDATESPRIVATE_H
