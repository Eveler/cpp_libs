#ifndef TRUSTEELOADER_P_H
#define TRUSTEELOADER_P_H

#include <QThread>

#include "trusteeloader.h"
#include "trusteelist.h"

#include <QHash>


class TrusteeLoader_P : public QThread
{
    Q_OBJECT
    friend class TrusteeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendTrusteeInfo( TrusteeInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    TrusteeList *m__Source;

    explicit TrusteeLoader_P( TrusteeLoader *parent );
    ~TrusteeLoader_P();

    TrusteeLoader * p_dptr() const;
};

#endif // TRUSTEELOADER_P_H
