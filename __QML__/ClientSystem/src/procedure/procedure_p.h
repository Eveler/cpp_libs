#ifndef PROCEDURE_P_H
#define PROCEDURE_P_H

#include <QObject>

#include "procedure.h"


class Procedure_P : public QObject
{
    Q_OBJECT
    friend class Procedure;


public:


signals:


public slots:


private:
    Procedure *m__Link;
    QString m__NullString;

    explicit Procedure_P( Procedure *parent );

    Procedure *p_dptr() const;
};

#endif // PROCEDURE_P_H
