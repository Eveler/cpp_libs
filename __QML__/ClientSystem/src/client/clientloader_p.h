#ifndef CLIENTLOADER_P_H
#define CLIENTLOADER_P_H

#include <QThread>

#include "clientloader.h"
#include "clientlist.h"

#include <QHash>


class ClientLoader_P : public QThread
{
    Q_OBJECT
    friend class ClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendClientInfo( ClientInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    ClientList *m__Source;

    explicit ClientLoader_P( ClientLoader *parent );
    ~ClientLoader_P();

    ClientLoader * p_dptr() const;
};

#endif // CLIENTLOADER_P_H
