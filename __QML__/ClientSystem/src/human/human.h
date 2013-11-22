#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>

#include "humaninfo.h"

#include <QtQml>


class Human_P;
class HumanList;

class Human : public QObject, public HumanInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Human)
    friend class HumanList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)


public:
    Human( HumanList *parent = 0 );
    Human( HumanList *parent, const HumanInfo &info );
    Human( HumanList *parent, Human *link );
    ~Human();

    Q_INVOKABLE HumanList * humanList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname( const QString &surname );

    const QString & firstname() const;
    void setFirstname( const QString &firstname );

    const QString & lastname() const;
    void setLastname( const QString &lastname );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & email() const;
    void setEmail( const QString &email );


signals:
    void indexChanged();
    void identifierChanged();
    void surnameChanged();
    void firstnameChanged();
    void lastnameChanged();
    void addressChanged();
    void phoneChanged();
    void emailChanged();


public slots:


private:
    Human_P *p;
};

QML_DECLARE_TYPE(Human)

#endif // HUMAN_H
