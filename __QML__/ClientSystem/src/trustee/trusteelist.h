#ifndef TRUSTEELIST_H
#define TRUSTEELIST_H

#include <QObject>

#include "trusteeinfo.h"

#include <QtQml>


class TrusteeList_P;
class TrusteeLoader;
class Trustee;

class TrusteeList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TrusteeList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QList<QObject *> list READ listAsQObjects NOTIFY countChanged)
    friend class TrusteeLoader;


  public:
    TrusteeList(QObject *parent = 0);
    ~TrusteeList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Trustee * trustee( int index ) const;
    Q_INVOKABLE int trusteeIndex( Trustee *trustee ) const;
    Q_INVOKABLE Trustee * addLink( Trustee *link ) const;

    const QList<Trustee *> & list() const;
    QList<QObject *> listAsQObjects() const;

    Q_INVOKABLE Trustee * find( QVariant identifier ) const;


  signals:
    void countChanged() const;
    void trusteeAdded( Trustee *trustee ) const;
    void trusteeRemoved( int index ) const;


  private:
    TrusteeList_P *p;


  private slots:
    void receivedTrusteeInfo( TrusteeInfo trusteeinfo ) const;
    void trusteeDestroyed();
};

QML_DECLARE_TYPE(TrusteeList)

#endif // TRUSTEELIST_H
