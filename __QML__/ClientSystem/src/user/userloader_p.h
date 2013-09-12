#ifndef USERLOADER_P_H
#define USERLOADER_P_H

#include <QThread>

#include "userloader.h"
#include "userlist.h"

#include <QHash>


class UserLoader_P : public QThread
{
    Q_OBJECT
    friend class UserLoader;


public:


signals:
    void sendError( QString errorText );
    void sendUserInfo( UserInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    UserList *m__Source;

    explicit UserLoader_P( UserLoader *parent );
    ~UserLoader_P();

    UserLoader * p_dptr() const;
};

#endif // USERLOADER_P_H
