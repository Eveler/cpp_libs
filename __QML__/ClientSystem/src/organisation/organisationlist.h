#ifndef ORGANISATIONLIST_H
#define ORGANISATIONLIST_H

#include <QObject>

#include "organisationinfo.h"

#include <QtQml>


class OrganisationList_P;
class OrganisationLoader;
class Organisation;

class OrganisationList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OrganisationList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class OrganisationLoader;


public:
    OrganisationList(QObject *parent = 0);
    ~OrganisationList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Organisation * organisation( int index ) const;
    Q_INVOKABLE int organisationIndex( Organisation *organisation ) const;
    Q_INVOKABLE Organisation * addLink( Organisation *link ) const;


signals:
    void countChanged() const;
    void organisationAdded( Organisation *organisation ) const;
    void organisationRemoved( int index ) const;


private:
    OrganisationList_P *p;


private slots:
    void receivedOrganisationInfo( OrganisationInfo organisationInfo ) const;
    void organisationDestroyed();
};

QML_DECLARE_TYPE(OrganisationList)

#endif // ORGANISATIONLIST_H
