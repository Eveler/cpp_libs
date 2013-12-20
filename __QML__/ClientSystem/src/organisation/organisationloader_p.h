#ifndef ORGANISATIONLOADER_P_H
#define ORGANISATIONLOADER_P_H

#include <QThread>

#include "organisationloader.h"
#include "organisationinfo.h"

#include <QHash>


class OrganisationLoader_P : public QThread
{
    Q_OBJECT
    friend class OrganisationLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( OrganisationInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit OrganisationLoader_P( OrganisationLoader *parent );
    ~OrganisationLoader_P();

    OrganisationLoader * p_dptr() const;
};

#endif // ORGANISATIONLOADER_P_H
