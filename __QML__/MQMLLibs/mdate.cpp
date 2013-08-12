#include "mdate.h"



MDate::MDate(QQuickItem *parent) :
    QQuickItem(parent)
{
}

QDate MDate::currentDate() const
{
    return QDate::currentDate();
}

QDate MDate::date( int year, int month, int day ) const
{
    return QDate( year, month, day );
}

int MDate::daysInMonth( int year, int month ) const
{
    return QDate( year, month, 1 ).daysInMonth();
}

int MDate::daysInYear( int year ) const
{
    return QDate( year, 1, 1 ).daysInYear();
}

int MDate::dayOfWeak( QDate date ) const
{
    return date.dayOfWeek();
}

int MDate::dayOfYear( QDate date ) const
{
    return date.dayOfYear();
}

QString MDate::longDayName( int weekday ) const
{
    return QDate::longDayName( weekday );
}

QString MDate::longMonthName( int month ) const
{
    return QDate::longMonthName( month );
}

QString MDate::shortDayName( int weekday ) const
{
    return QDate::shortDayName( weekday );
}

QString MDate::shortMonthName( int month ) const
{
    return QDate::shortMonthName( month );
}

QDate MDate::addDays( QDate date, int days ) const
{
    return date.addDays( days );
}

