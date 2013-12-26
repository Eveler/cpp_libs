#ifndef PROCEDURELOADER_P_H
#define PROCEDURELOADER_P_H

#include <QThread>

#include "procedureloader.h"
#include "procedureinfo.h"

#include <QSqlQuery>


class ProcedureLoader_P : public QThread
{
    Q_OBJECT
    friend class ProcedureLoader;


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

    explicit ProcedureLoader_P( ProcedureLoader *parent );
    ~ProcedureLoader_P();

    ProcedureLoader * p_dptr() const;

    ProcedureInfo * newInfo();
};

#endif // PROCEDURELOADER_P_H
