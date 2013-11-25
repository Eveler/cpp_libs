#ifndef ASSESSMENTTYPE_P_H
#define ASSESSMENTTYPE_P_H

#include <QObject>

#include "assessmenttype.h"


class Assessmenttype_P : public QObject
{
    Q_OBJECT
    friend class Assessmenttype;


public:


signals:


public slots:


private:
    Assessmenttype *m__Link;
    QString m__NullString;

    explicit Assessmenttype_P( Assessmenttype *parent );

    Assessmenttype *p_dptr() const;
};

#endif // ASSESSMENTTYPE_P_H
