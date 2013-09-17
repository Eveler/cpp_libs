#include "humaninfo.h"


HumanInfo::HumanInfo() :
    m__Identifier(QVariant()),
    m__Surname(QString()),
    m__Firstname(QString()),
    m__Lastname(QString())
{
}

HumanInfo::HumanInfo( const HumanInfo &other ) :
    m__Identifier(other.identifier()),
    m__Surname(other.surname()),
    m__Firstname(other.firstname()),
    m__Lastname(other.lastname())
{
}

HumanInfo::~HumanInfo()
{
}

QVariant HumanInfo::identifier() const
{
    return m__Identifier;
}

void HumanInfo::setIdentifier( QVariant identifier )
{
    m__Identifier = identifier;
}

const QString & HumanInfo::surname() const
{
    return m__Surname;
}

void HumanInfo::setSurname( const QString &surname )
{
    m__Surname = surname;
}

const QString & HumanInfo::firstname() const
{
    return m__Firstname;
}

void HumanInfo::setFirstname( const QString &firstname )
{
    m__Firstname = firstname;
}

const QString & HumanInfo::lastname() const
{
    return m__Lastname;
}

void HumanInfo::setLastname( const QString &lastname )
{
    m__Lastname = lastname;
}
