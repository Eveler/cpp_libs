#ifndef DOCTYPELIST_P_H
#define DOCTYPELIST_P_H

#include <QObject>

#include "doctypelist.h"
#include "doctype.h"


class DoctypeList_P : public QObject
{
    Q_OBJECT
    friend class DoctypeList;


  public:


  signals:


  public slots:


  private:
    QList<Doctype *> m__Doctypes;

    explicit DoctypeList_P( DoctypeList *parent );
    ~DoctypeList_P();

    DoctypeList * p_dptr() const;
};

#endif // DOCTYPELIST_P_H
