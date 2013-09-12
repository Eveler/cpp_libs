#ifndef DOCTYPE_P_H
#define DOCTYPE_P_H

#include <QObject>

#include "doctype.h"


class Doctype_P : public QObject
{
    Q_OBJECT
    friend class Doctype;


public:


signals:


public slots:


private:
    Doctype *m__Link;
    QString m__NullString;

    explicit Doctype_P( Doctype *parent );

    Doctype *p_dptr() const;
};

#endif // DOCTYPE_P_H
