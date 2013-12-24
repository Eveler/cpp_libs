#include "mqml.h"

#include "Tree/treeitem.h"

#include <QDebug>


MQML::MQML(QObject *parent) :
  QObject(parent)
{
}

TreeItem * MQML::createTreeItem( QVariant value ) const
{
  TreeItem *result = new TreeItem;
  result->setValue( value );
  return result;
}

QDate MQML::invalidDate() const
{
  return QDate();
}

bool MQML::isValidDate( QDate date ) const
{
  return date.isValid();
}

int MQML::daysInMonth( QDate date ) const
{
  return date.daysInMonth();
}

int MQML::daysInMonth( int year, int month ) const
{
  return QDate( year, month, 1 ).daysInMonth();
}

int MQML::daysBetween( QDate arg1, QDate arg2 ) const
{
  return arg1.daysTo( arg2 );
}

qint64 MQML::millisecondsBetween( QDateTime arg1, QDateTime arg2 ) const
{
  return arg1.msecsTo( arg2 );
}

QDateTime MQML::addMSecs( QDateTime arg1, int msecs )
{
  return arg1.addMSecs( msecs );
}
