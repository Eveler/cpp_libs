#include "user_p.h"


User_P::User_P(User *parent) :
    QObject(parent)
{
}

User * User_P::p_dptr() const
{
    return qobject_cast<User *>( parent() );
}
