#ifndef CLIENTLOADER_P_H
#define CLIENTLOADER_P_H

#include <QThread>

#include "clientloader.h"
#include "clientinfo.h"

#include <QHash>


class ClientLoader_P : public QThread
{
    Q_OBJECT
    friend class ClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( ClientInfo * );
    void countChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    int m__Count;

    explicit ClientLoader_P( ClientLoader *parent );
    ~ClientLoader_P();

    ClientLoader * p_dptr() const;
};

#endif // CLIENTLOADER_P_H
