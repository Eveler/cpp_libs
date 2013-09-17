#ifndef PROCEDURELOADER_P_H
#define PROCEDURELOADER_P_H

#include <QThread>

#include "procedureloader.h"
#include "procedurelist.h"

#include <QHash>


class ProcedureLoader_P : public QThread
{
    Q_OBJECT
    friend class ProcedureLoader;


public:


signals:
    void sendError( QString errorText );
    void sendProcedureInfo( ProcedureInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    ProcedureList *m__Source;

    explicit ProcedureLoader_P( ProcedureLoader *parent );
    ~ProcedureLoader_P();

    ProcedureLoader * p_dptr() const;
};

#endif // PROCEDURELOADER_P_H
