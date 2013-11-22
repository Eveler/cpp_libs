#ifndef declarCLIENTLOADER_P_H
#define declarCLIENTLOADER_P_H

#include <QThread>

#include "declarclientloader.h"
#include "declarclientlist.h"

#include <QHash>


class DeclarClientLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendDeclarClientInfo( DeclarClientInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    DeclarClientList *m__Source;

    explicit DeclarClientLoader_P( DeclarClientLoader *parent );
    ~DeclarClientLoader_P();

    DeclarClientLoader * p_dptr() const;
};

#endif // declarCLIENTLOADER_P_H
