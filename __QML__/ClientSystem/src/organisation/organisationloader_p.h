#ifndef ORGANISATIONLOADER_P_H
#define ORGANISATIONLOADER_P_H

#include <QThread>

#include "organisationloader.h"
#include "organisationlist.h"

#include <QHash>


class OrganisationLoader_P : public QThread
{
    Q_OBJECT
    friend class OrganisationLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendOrganisationInfo( OrganisationInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    OrganisationList *m__Source;

    explicit OrganisationLoader_P( OrganisationLoader *parent );
    ~OrganisationLoader_P();

    OrganisationLoader * p_dptr() const;
};

#endif // ORGANISATIONLOADER_P_H
