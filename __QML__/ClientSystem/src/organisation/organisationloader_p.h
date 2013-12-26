#ifndef ORGANISATIONLOADER_P_H
#define ORGANISATIONLOADER_P_H

#include <QThread>

#include "organisationloader.h"
#include "organisationinfo.h"

#include <QSqlQuery>


class OrganisationLoader_P : public QThread
{
    Q_OBJECT
    friend class OrganisationLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit OrganisationLoader_P( OrganisationLoader *parent );
    ~OrganisationLoader_P();

    OrganisationLoader * p_dptr() const;

    OrganisationInfo * newInfo();
};

#endif // ORGANISATIONLOADER_P_H
