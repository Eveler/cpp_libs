#ifndef DECLARLIST_P_H
#define DECLARLIST_P_H

#include <QObject>

#include "declarlist.h"
#include "declar.h"


class DeclarList_P : public QObject
{
    Q_OBJECT
    friend class DeclarList;


  public:


  signals:


  public slots:


  private:
    QList<Declar *> m__Declars;

    explicit DeclarList_P( DeclarList *parent );
    ~DeclarList_P();

    DeclarList * p_dptr() const;
};

#endif // DECLARLIST_P_H
