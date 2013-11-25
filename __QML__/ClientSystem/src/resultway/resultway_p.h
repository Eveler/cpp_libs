#ifndef RESULTWAY_P_H
#define RESULTWAY_P_H

#include <QObject>

#include "resultway.h"


class Resultway_P : public QObject
{
    Q_OBJECT
    friend class Resultway;


public:


signals:


public slots:


private:
    Resultway *m__Link;
    QString m__NullString;

    explicit Resultway_P( Resultway *parent );

    Resultway *p_dptr() const;
};

#endif // RESULTWAY_P_H
