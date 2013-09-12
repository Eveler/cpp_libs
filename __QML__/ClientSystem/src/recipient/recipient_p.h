#ifndef RECIPIENT_P_H
#define RECIPIENT_P_H

#include <QObject>

#include "recipient.h"


class Recipient_P : public QObject
{
    Q_OBJECT
    friend class Recipient;


public:


signals:


public slots:


private:
    Recipient *m__Link;
    QString m__NullString;

    explicit Recipient_P( Recipient *parent );

    Recipient *p_dptr() const;
};

#endif // RECIPIENT_P_H
