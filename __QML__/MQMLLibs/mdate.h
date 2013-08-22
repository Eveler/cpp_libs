#ifndef MDATE_H
#define MDATE_H

#include <QQuickItem>

#include <QDate>


class MDate : public QQuickItem
{
    Q_OBJECT

public:

    explicit MDate(QQuickItem *parent = 0);

    Q_INVOKABLE QDate currentDate() const;
    Q_INVOKABLE QDate date( int year, int month, int day ) const;
    Q_INVOKABLE int daysInMonth( int year, int month ) const;
    Q_INVOKABLE int daysInYear( int year ) const;
    Q_INVOKABLE int dayOfWeak( QDate date ) const;
    Q_INVOKABLE int dayOfYear( QDate date ) const;
    Q_INVOKABLE QString longDayName( int weekday ) const;
    Q_INVOKABLE QString longMonthName( int month ) const;
    Q_INVOKABLE QString shortDayName( int weekday ) const;
    Q_INVOKABLE QString shortMonthName( int month ) const;
    Q_INVOKABLE QDate addDays( QDate date, int days ) const;


signals:


public slots:
};

#endif // MDATE_H
