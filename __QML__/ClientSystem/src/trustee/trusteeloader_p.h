#ifndef TRUSTEELOADER_P_H
#define TRUSTEELOADER_P_H

#include <QThread>

#include "trusteeloader.h"
#include "trusteeinfo.h"

#include <QHash>


class TrusteeLoader_P : public QThread
{
    Q_OBJECT
    friend class TrusteeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( TrusteeInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit TrusteeLoader_P( TrusteeLoader *parent );
    ~TrusteeLoader_P();

    TrusteeLoader * p_dptr() const;
};

#endif // TRUSTEELOADER_P_H
