#include "userinfo.h"


UserInfo::UserInfo() :
    m__Identifier(QVariant()),
    m__Surname(QString()),
    m__Firstname(QString()),
    m__Lastname(QString()),
    m__Post(-1),
    m__Department(-1),
    m__Isactive(false),
    m__Dismissed(false),
    m__Dblogin(QString()),
    m__Direction(-1)
{
}

UserInfo::UserInfo( const UserInfo &other ) :
    m__Identifier(other.identifier()),
    m__Surname(other.surname()),
    m__Firstname(other.firstname()),
    m__Lastname(other.lastname()),
    m__Post(other.post()),
    m__Department(other.department()),
    m__Isactive(other.isactive()),
    m__Dismissed(other.dismissed()),
    m__Dblogin(other.dblogin()),
    m__Direction(other.direction())
{
}

UserInfo::~UserInfo()
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

int UserInfo::post() const
{
    return m__Post;
}

void UserInfo::setPost( int post )
{
    m__Post = post;
}

int UserInfo::department() const
{
    return m__Department;
}

void UserInfo::setDepartment( int department )
{
    m__Department = department;
}

bool UserInfo::isactive() const
{
    return m__Isactive;
}

void UserInfo::setIsactive( bool isactive )
{
    m__Isactive = isactive;
}

bool UserInfo::dismissed() const
{
    return m__Dismissed;
}

void UserInfo::setDismissed( bool dismissed )
{
    m__Dismissed = dismissed;
}

const QString & UserInfo::dblogin() const
{
    return m__Dblogin;
}

void UserInfo::setDblogin( const QString &dblogin )
{
    m__Dblogin = dblogin;
}

int UserInfo::direction() const
{
    return m__Direction;
}

void UserInfo::setDirection( int direction )
{
    m__Direction = direction;
}
