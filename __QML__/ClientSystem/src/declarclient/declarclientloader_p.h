#ifndef declarCLIENTLOADER_P_H
#define declarCLIENTLOADER_P_H

#include <QThread>

#include "declarclientloader.h"
#include "declarclientinfo.h"

#include <QSqlQuery>


class DeclarClientLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarClientLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit DeclarClientLoader_P( DeclarClientLoader *parent );
    ~DeclarClientLoader_P();

    DeclarClientLoader * p_dptr() const;

    DeclarClientInfo * newInfo();
};

#endif // declarCLIENTLOADER_P_H
