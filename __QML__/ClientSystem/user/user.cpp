#include "user.h"

#include "user_p.h"
#include "userlist.h"

#define INFO_REF UserInfo *info = static_cast<UserInfo *>( p->p_dptr() );

User::User( UserList *parent ) :
    QObject(parent), UserInfo()
{
    p = new User_P( this );
}

User::User( UserList *parent, const UserInfo &info ) :
    QObject(parent), UserInfo(info)
{
    p = new User_P( this );
}

User::User( UserList *parent, User *link ) :
    QObject(parent), UserInfo()
{
    p = new User_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

User::~User()
{
    delete p;
    p = NULL;
}

UserList * User::userList() const
{
    return qobject_cast<UserList *>( parent() );
}

int User::index() const
{
    UserList *ul = userList();
    if ( ul == NULL ) return -1;

    return ul->userIndex( p->p_dptr() );
}

QVariant User::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void User::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & User::surname() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->surname();
    return info->surname();
}

void User::setSurname( const QString &surname )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setSurname( surname );
    else info->setSurname( surname );
    emit surnameChanged();
}

const QString & User::firstname() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->firstname();
    return info->firstname();
}

void User::setFirstname( const QString &firstname )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setFirstname( firstname );
    else info->setFirstname( firstname );
    emit firstnameChanged();
}

const QString & User::lastname() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->lastname();
    return info->lastname();
}

void User::setLastname( const QString &lastname )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setLastname( lastname );
    else info->setLastname( lastname );
    emit lastnameChanged();
}

void User::resetIndex()
{

}
