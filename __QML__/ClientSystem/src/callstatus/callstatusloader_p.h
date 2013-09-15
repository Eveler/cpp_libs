#ifndef CALLSTATUSLOADER_P_H
#define CALLSTATUSLOADER_P_H

#include <QThread>

#include "callstatusloader.h"
#include "callstatuslist.h"

#include <QHash>


class CallstatusLoader_P : public QThread
{
    Q_OBJECT
    friend class CallstatusLoader;


public:


signals:
    void sendError( QString errorText );
    void sendCallstatusInfo( CallstatusInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    CallstatusList *m__Source;
    QVariant m__LoadIdentifier;

    explicit CallstatusLoader_P( CallstatusLoader *parent );
    ~CallstatusLoader_P();

    CallstatusLoader * p_dptr() const;
};

#endif // CALLSTATUSLOADER_P_H
