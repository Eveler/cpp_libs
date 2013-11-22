#ifndef ORGANISATIONLIST_P_H
#define ORGANISATIONLIST_P_H

#include <QObject>

#include "organisationlist.h"
#include "organisation.h"


class OrganisationList_P : public QObject
{
    Q_OBJECT
    friend class OrganisationList;


public:


signals:


public slots:


private:
    QList<Organisation *> m__Organisations;

    explicit OrganisationList_P( OrganisationList *parent );
    ~OrganisationList_P();

    OrganisationList * p_dptr() const;
};

#endif // ORGANISATIONLIST_P_H
