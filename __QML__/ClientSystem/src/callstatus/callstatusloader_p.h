#ifndef CALLSTATUSLOADER_P_H
#define CALLSTATUSLOADER_P_H

#include <QThread>

#include "callstatusloader.h"
#include "callstatusinfo.h"

#include <QHash>


class CallstatusLoader_P : public QThread
{
    Q_OBJECT
    friend class CallstatusLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( CallstatusInfo * );
    void countChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QVariant m__LoadIdentifier;
    int m__Count;

    explicit CallstatusLoader_P( CallstatusLoader *parent );
    ~CallstatusLoader_P();

    CallstatusLoader * p_dptr() const;
};

#endif // CALLSTATUSLOADER_P_H
