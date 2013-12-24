#ifndef CLIENTLOADER_P_H
#define CLIENTLOADER_P_H

#include <QThread>

#include "clientloader.h"
#include "clientinfo.h"

#include <QSqlQuery>


class ClientLoader_P : public QThread
{
    Q_OBJECT
    friend class ClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit ClientLoader_P( ClientLoader *parent );
    ~ClientLoader_P();

    ClientLoader * p_dptr() const;

    ClientInfo * newInfo();
};

#endif // CLIENTLOADER_P_H
