#ifndef TRUSTEE_P_H
#define TRUSTEE_P_H

#include <QObject>

#include "trustee.h"


class Trustee_P : public QObject
{
    Q_OBJECT
    friend class Trustee;


public:


signals:


public slots:


private:
    Trustee *m__Link;
    QString m__NullString;

    explicit Trustee_P( Trustee *parent );

    Trustee *p_dptr() const;
};

#endif // TRUSTEE_P_H
