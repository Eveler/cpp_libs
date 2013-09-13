#ifndef HUMAN_P_H
#define HUMAN_P_H

#include <QObject>

#include "human.h"


class Human_P : public QObject
{
    Q_OBJECT
    friend class Human;


public:


signals:


public slots:


private:
    Human *m__Link;
    QString m__NullString;

    explicit Human_P( Human *parent );

    Human *p_dptr() const;
};

#endif // HUMAN_P_H
