#include "userinfo.h"

UserInfo::UserInfo() :
    m__Identifier(QVariant()),
    m__Surname(QString()),
    m__Firstname(QString()),
    m__Lastname(QString())
{
}

UserInfo::UserInfo( const UserInfo &other ) :
    m__Identifier(other.identifier()),
    m__Surname(other.surname()),
    m__Firstname(other.firstname()),
    m__Lastname(other.lastname())
{
}

QVariant UserInfo::identifier() const
{
    return m__Identifier;
}

void UserInfo::setIdentifier( QVariant identifier )
{
    m__Identifier = identifier;
}

const QString & UserInfo::surname() const
{
    return m__Surname;
}

void UserInfo::setSurname( const QString &surname )
{
    m__Surname = surname;
}

const QString & UserInfo::firstname() const
{
    return m__Firstname;
}

void UserInfo::setFirstname( const QString &firstname )
{
    m__Firstname = firstname;
}

const QString & UserInfo::lastname() const
{
    return m__Lastname;
}

void UserInfo::setLastname( const QString &lastname )
{
    m__Lastname = lastname;
}
