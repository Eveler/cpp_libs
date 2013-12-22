#ifndef declarCLIENTLOADER_P_H
#define declarCLIENTLOADER_P_H

#include <QThread>

#include "declarclientloader.h"
#include "declarclientinfo.h"

#include <QHash>


class DeclarClientLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( DeclarClientInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit DeclarClientLoader_P( DeclarClientLoader *parent );
    ~DeclarClientLoader_P();

    DeclarClientLoader * p_dptr() const;
};

#endif // declarCLIENTLOADER_P_H
