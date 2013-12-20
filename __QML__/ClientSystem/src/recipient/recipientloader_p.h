#ifndef RECIPIENTLOADER_P_H
#define RECIPIENTLOADER_P_H

#include <QThread>

#include "recipientloader.h"
#include "recipientinfo.h"

#include <QHash>


class RecipientLoader_P : public QThread
{
    Q_OBJECT
    friend class RecipientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( RecipientInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit RecipientLoader_P( RecipientLoader *parent );
    ~RecipientLoader_P();

    RecipientLoader * p_dptr() const;
};

#endif // RECIPIENTLOADER_P_H
