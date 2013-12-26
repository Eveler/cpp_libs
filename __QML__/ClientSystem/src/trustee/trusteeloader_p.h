#ifndef TRUSTEELOADER_P_H
#define TRUSTEELOADER_P_H

#include <QThread>

#include "trusteeloader.h"
#include "trusteeinfo.h"

#include <QSqlQuery>


class TrusteeLoader_P : public QThread
{
    Q_OBJECT
    friend class TrusteeLoader;


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

    explicit TrusteeLoader_P( TrusteeLoader *parent );
    ~TrusteeLoader_P();

    TrusteeLoader * p_dptr() const;

    TrusteeInfo * newInfo();
};

#endif // TRUSTEELOADER_P_H
