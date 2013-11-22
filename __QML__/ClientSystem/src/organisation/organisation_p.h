#ifndef ORGANISATION_P_H
#define ORGANISATION_P_H

#include <QObject>

#include "organisation.h"


class Organisation_P : public QObject
{
    Q_OBJECT
    friend class Organisation;


public:


signals:


public slots:


private:
    Organisation *m__Link;
    QString m__NullString;

    explicit Organisation_P( Organisation *parent );

    Organisation *p_dptr() const;
};

#endif // ORGANISATION_P_H
