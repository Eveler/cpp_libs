#ifndef CALLSTATUSLOADER_P_H
#define CALLSTATUSLOADER_P_H

#include <QThread>

#include "callstatusloader.h"
#include "callstatusinfo.h"

#include <QSqlQuery>


class CallstatusLoader_P : public QThread
{
    Q_OBJECT
    friend class CallstatusLoader;


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
    QVariant m__LoadIdentifier;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit CallstatusLoader_P( CallstatusLoader *parent );
    ~CallstatusLoader_P();

    CallstatusLoader * p_dptr() const;

    CallstatusInfo * newInfo();
};

#endif // CALLSTATUSLOADER_P_H
