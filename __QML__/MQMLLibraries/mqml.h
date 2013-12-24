#ifndef MQML_H
#define MQML_H

#include <QObject>

#include <QtQml>


class TreeItem;

class MQML : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( MQML )


  public:
    explicit MQML(QObject *parent = 0);

    Q_INVOKABLE TreeItem * createTreeItem( QVariant value = QVariant() ) const;

    Q_INVOKABLE QDate invalidDate() const;
    Q_INVOKABLE bool isValidDate( QDate date ) const;
    Q_INVOKABLE int daysInMonth( QDate date ) const;
    Q_INVOKABLE int daysInMonth( int year, int month ) const;
    Q_INVOKABLE int daysBetween( QDate arg1, QDate arg2 ) const;
    Q_INVOKABLE qint64 millisecondsBetween( QDateTime arg1, QDateTime arg2 ) const;
    Q_INVOKABLE QDateTime addMSecs( QDateTime arg1, int msecs );
};

QML_DECLARE_TYPE(MQML)

#endif // MQML_H
