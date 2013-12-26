#ifndef RECIPIENTLOADER_P_H
#define RECIPIENTLOADER_P_H

#include <QThread>

#include "recipientloader.h"
#include "recipientinfo.h"

#include <QSqlQuery>


class RecipientLoader_P : public QThread
{
    Q_OBJECT
    friend class RecipientLoader;


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

    explicit RecipientLoader_P( RecipientLoader *parent );
    ~RecipientLoader_P();

    RecipientLoader * p_dptr() const;

    RecipientInfo * newInfo();
};

#endif // RECIPIENTLOADER_P_H
