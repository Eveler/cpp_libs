#include "userlist_p.h"

#include "userlist.h"


void UserList_P::run()
{
    emit sendUser( new User() );
}

UserList_P::UserList_P( UserList *parent ) :
    QThread(parent),
    m__ErrorLastId(-1),
    m__Errors(QHash<int, QString>()),
    m__ConnectionName(QString()),
    m__Users(QList<User *>())
{
    connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
    connect( this, SIGNAL(sendUser(User*)), parent, SLOT(receivedUser(User*)) );
}

UserList_P::~UserList_P()
{
}

UserList * UserList_P::p_dptr() const
{
    return qobject_cast<UserList *>( parent() );
}

