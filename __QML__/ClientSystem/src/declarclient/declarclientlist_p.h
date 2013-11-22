#ifndef declarCLIENTLIST_P_H
#define declarCLIENTLIST_P_H

#include <QObject>

#include "declarclientlist.h"
#include "declarclient.h"


class DeclarClientList_P : public QObject
{
    Q_OBJECT
    friend class DeclarClientList;


  public:


  signals:


  public slots:


  private:
    QList<DeclarClient *> m__DeclarClients;

    explicit DeclarClientList_P( DeclarClientList *parent );
    ~DeclarClientList_P();

    DeclarClientList * p_dptr() const;
};

#endif // declarCLIENTLIST_P_H
