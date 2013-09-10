#include "userinfo.h"

UserInfo::UserInfo() :
    m__Identifier(QVariant())
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
