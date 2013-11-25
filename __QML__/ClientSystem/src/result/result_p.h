#ifndef RESULT_P_H
#define RESULT_P_H

#include <QObject>

#include "result.h"


class Result_P : public QObject
{
    Q_OBJECT
    friend class Result;


public:


signals:


public slots:


private:
    Result *m__Link;
    QString m__NullString;

    explicit Result_P( Result *parent );

    Result *p_dptr() const;
};

#endif // RESULT_P_H
