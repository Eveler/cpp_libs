#ifndef MENU_PERIODDATES_H
#define MENU_PERIODDATES_H

#include <QMenu>

#include "lib_export.h"

#include <QDate>


class Menu_PeriodDatesPrivate;

class EXPORT Menu_PeriodDates : public QMenu
{
  friend class Menu_PeriodDatesPrivate;

  Q_OBJECT
public:
  enum Period {Daily = 0, Weekly, Monthly, Quarterly, Semiannual, Yearly};

  explicit Menu_PeriodDates(QWidget *parent = 0);
  ~Menu_PeriodDates();

  const QDate & firstDate() const;
  const QDate & lastDate() const;

  void setCurrentDateIcon( const QIcon &icon );

  void setPeriodEnabled( Period period, bool enabled );
  bool isPeriodHidden() const;


signals:
  void periodHovered( QDate firstDate, QDate lastDate );
  void periodChanged( QDate firstDate, QDate lastDate );


public slots:


private:
  Menu_PeriodDatesPrivate *m__P;

  QPair<QDate, QDate> periodByAction( QAction *action );


private slots:
  void actionHovered( QAction *action );
  void actionTriggered( QAction *action );
};

#endif // MENU_PERIODDATES_H
