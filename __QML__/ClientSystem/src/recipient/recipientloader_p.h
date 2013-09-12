#ifndef RECIPIENTLOADER_P_H
#define RECIPIENTLOADER_P_H

#include <QThread>

#include "recipientloader.h"
#include "recipientlist.h"

#include <QHash>


class RecipientLoader_P : public QThread
{
    Q_OBJECT
    friend class RecipientLoader;


public:


signals:
    void sendError( QString errorText );
    void sendRecipientInfo( RecipientInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    RecipientList *m__Source;

    explicit RecipientLoader_P( RecipientLoader *parent );
    ~RecipientLoader_P();

    RecipientLoader * p_dptr() const;
};

#endif // RECIPIENTLOADER_P_H
