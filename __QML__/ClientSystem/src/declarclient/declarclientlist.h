#ifndef declarCLIENTLIST_H
#define declarCLIENTLIST_H

#include <QObject>

#include "declarclientinfo.h"

#include <QtQml>


class DeclarClientList_P;
class DeclarClientLoader;
class DeclarClient;

class DeclarClientList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarClientList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class DeclarClientLoader;


  public:
    DeclarClientList(QObject *parent = 0);
    ~DeclarClientList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE DeclarClient * declarclient( int index ) const;
    Q_INVOKABLE int declarclientIndex( DeclarClient *declarclient ) const;
    Q_INVOKABLE DeclarClient * addLink( DeclarClient *link ) const;


  signals:
    void countChanged() const;
    void declarclientAdded( DeclarClient *declarclient ) const;
    void declarclientRemoved( int index ) const;


  private:
    DeclarClientList_P *p;


  private slots:
    void receivedDeclarClientInfo( DeclarClientInfo declarclientinfo ) const;
    void declarclientDestroyed();
};

QML_DECLARE_TYPE(DeclarClientList)

#endif // declarCLIENTLIST_H
