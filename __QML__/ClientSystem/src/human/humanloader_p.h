#ifndef HUMANLOADER_P_H
#define HUMANLOADER_P_H

#include <QThread>

#include "humanloader.h"
#include "humanlist.h"

#include <QHash>


class HumanLoader_P : public QThread
{
    Q_OBJECT
    friend class HumanLoader;


public:


signals:
    void sendError( QString errorText );
    void sendHumanInfo( HumanInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    HumanList *m__Source;

    explicit HumanLoader_P( HumanLoader *parent );
    ~HumanLoader_P();

    HumanLoader * p_dptr() const;
};

#endif // HUMANLOADER_P_H
