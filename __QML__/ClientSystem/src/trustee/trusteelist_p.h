#ifndef TRUSTEELIST_P_H
#define TRUSTEELIST_P_H

#include <QObject>

#include "trusteelist.h"
#include "trustee.h"


class TrusteeList_P : public QObject
{
    Q_OBJECT
    friend class TrusteeList;


  public:


  signals:


  public slots:


  private:
    QList<Trustee *> m__Trustees;

    explicit TrusteeList_P( TrusteeList *parent );
    ~TrusteeList_P();

    TrusteeList * p_dptr() const;
};

#endif // TRUSTEELIST_P_H
