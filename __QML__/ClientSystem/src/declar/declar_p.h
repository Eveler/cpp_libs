#ifndef DECLAR_P_H
#define DECLAR_P_H

#include <QObject>

#include "declar.h"


class Declar_P : public QObject
{
    Q_OBJECT
    friend class Declar;


public:


signals:


public slots:


private:
    Declar *m__Link;
    QString m__NullString;

    explicit Declar_P( Declar *parent );

    Declar *p_dptr() const;
};

#endif // DECLAR_P_H
