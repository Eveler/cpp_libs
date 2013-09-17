#include "user_p.h"


User_P::User_P(User *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

User * User_P::p_dptr() const
{
    return qobject_cast<User *>( parent() );
}
