#ifndef RESULTWAYLIST_P_H
#define RESULTWAYLIST_P_H

#include <QObject>

#include "resultwaylist.h"
#include "resultway.h"


class ResultwayList_P : public QObject
{
    Q_OBJECT
    friend class ResultwayList;


  public:


  signals:


  public slots:


  private:
    QList<Resultway *> m__Resultways;

    explicit ResultwayList_P( ResultwayList *parent );
    ~ResultwayList_P();

    ResultwayList * p_dptr() const;
};

#endif // RESULTWAYLIST_P_H
