#ifndef USERINFO_H
#define USERINFO_H

#include <QtCore>

class UserInfo
{
public:
    UserInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

private:
    QVariant m__Identifier;
};

#endif // USERINFO_H
