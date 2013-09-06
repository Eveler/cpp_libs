#include "userlist.h"

UserList::UserList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

UserList::~UserList()
{
}

QString UserList::error( int operationId ) const
{
    return QString();
}

const QString & UserList::connectionName() const
{
    return QString();
}

bool UserList::setConnectionName( const QString &connectionName ) const
{
    return true;
}

bool UserList::load() const
{
    return true;
}

int UserList::count() const
{
    return 0;
}
