#ifndef DOCTYPELIST_H
#define DOCTYPELIST_H

#include <QObject>

#include "doctypeinfo.h"

#include <QtQml>


class DoctypeList_P;
class DoctypeLoader;
class Doctype;

class DoctypeList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DoctypeList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class DoctypeLoader;


  public:
    DoctypeList(QObject *parent = 0);
    ~DoctypeList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Doctype * doctype( int index ) const;
    Q_INVOKABLE int doctypeIndex( Doctype *doctype ) const;
    Q_INVOKABLE Doctype * addLink( Doctype *link ) const;

    Q_INVOKABLE Doctype * find( QVariant identifier ) const;


  signals:
    void countChanged() const;
    void doctypeAdded( Doctype *doctype ) const;
    void doctypeRemoved( int index ) const;


  private:
    DoctypeList_P *p;


  private slots:
    void receivedDoctypeInfo( DoctypeInfo doctypeinfo ) const;
    void doctypeDestroyed();
};

QML_DECLARE_TYPE(DoctypeList)

#endif // DOCTYPELIST_H
