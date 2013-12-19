#ifndef ORGANISATION_H
#define ORGANISATION_H

#include <QObject>

#include "organisationinfo.h"

#include <QtQml>


class Organisation_P;
class OrganisationList;

class Organisation : public QObject, public OrganisationInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Organisation)
    friend class OrganisationList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString fullname READ fullname WRITE setFullname NOTIFY fullnameChanged)
    Q_PROPERTY(QVariant humanIdentifier READ humanIdentifier
               WRITE setHumanIdentifier NOTIFY humanIdentifierChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)


public:
    Organisation( OrganisationList *parent = 0 );
    Organisation( OrganisationList *parent, const OrganisationInfo &info );
    Organisation( OrganisationList *parent, Organisation *link );
    ~Organisation();

    Q_INVOKABLE OrganisationList * organisationList() const;

    int index() const;

    void setOrganisationInfo( const OrganisationInfo &info );

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & fullname() const;
    void setFullname( const QString &fullname );

    QVariant humanIdentifier() const;
    void setHumanIdentifier( QVariant humanIdentifier );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & email() const;
    void setEmail( const QString &email );


signals:
    void indexChanged();
    void identifierChanged();
    void fullnameChanged();
    void humanIdentifierChanged();
    void addressChanged();
    void phoneChanged();
    void emailChanged();


public slots:


private:
    Organisation_P *p;
};

QML_DECLARE_TYPE(Organisation)

#endif // ORGANISATION_H
