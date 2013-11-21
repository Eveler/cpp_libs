#ifndef SERVICE_P_H
#define SERVICE_P_H

#include <QObject>

#include "service.h"


class Service_P : public QObject
{
    Q_OBJECT
    friend class Service;


  public:


  signals:


  public slots:


  private:
    Service *m__Link;
    QString m__NullString;

    explicit Service_P( Service *parent );

    Service *p_dptr() const;
};

#endif // SERVICE_P_H
