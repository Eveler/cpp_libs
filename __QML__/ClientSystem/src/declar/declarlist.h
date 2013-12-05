#ifndef DECLARLIST_H
#define DECLARLIST_H

#include <QObject>

#include "declarinfo.h"

#include <QtQml>


class DeclarList_P;
class DeclarLoader;
class Declar;

class DeclarList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class DeclarLoader;


  public:
    DeclarList(QObject *parent = 0);
    ~DeclarList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Declar * declar( int index ) const;
    Q_INVOKABLE int declarIndex( Declar *declar ) const;
    Q_INVOKABLE Declar * addLink( Declar *link ) const;

    Q_INVOKABLE Declar * find( QVariant identifier ) const;


  signals:
    void countChanged() const;
    void declarAdded( Declar *declar ) const;
    void declarRemoved( int index ) const;


  private:
    DeclarList_P *p;


  private slots:
    void receivedDeclarInfo( DeclarInfo declarinfo ) const;
    void declarDestroyed();
};

QML_DECLARE_TYPE(DeclarList)

#endif // DECLARLIST_H
