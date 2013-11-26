#ifndef RESULTLIST_P_H
#define RESULTLIST_P_H

#include <QObject>

#include "resultlist.h"
#include "result.h"


class ResultList_P : public QObject
{
    Q_OBJECT
    friend class ResultList;


  public:


  signals:


  public slots:


  private:
    QList<Result *> m__Results;

    explicit ResultList_P( ResultList *parent );
    ~ResultList_P();

    ResultList * p_dptr() const;
};

#endif // RESULTLIST_P_H
