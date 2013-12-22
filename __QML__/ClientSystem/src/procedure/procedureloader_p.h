#ifndef PROCEDURELOADER_P_H
#define PROCEDURELOADER_P_H

#include <QThread>

#include "procedureloader.h"
#include "procedureinfo.h"

#include <QHash>


class ProcedureLoader_P : public QThread
{
    Q_OBJECT
    friend class ProcedureLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( ProcedureInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit ProcedureLoader_P( ProcedureLoader *parent );
    ~ProcedureLoader_P();

    ProcedureLoader * p_dptr() const;
};

#endif // PROCEDURELOADER_P_H
