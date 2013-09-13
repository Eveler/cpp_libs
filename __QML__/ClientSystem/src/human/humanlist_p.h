#ifndef HUMANLIST_P_H
#define HUMANLIST_P_H

#include <QObject>

#include "humanlist.h"
#include "human.h"


class HumanList_P : public QObject
{
    Q_OBJECT
    friend class HumanList;


public:


signals:


public slots:


private:
    QList<Human *> m__Humans;

    explicit HumanList_P( HumanList *parent );
    ~HumanList_P();

    HumanList * p_dptr() const;
};

#endif // HUMANLIST_P_H
