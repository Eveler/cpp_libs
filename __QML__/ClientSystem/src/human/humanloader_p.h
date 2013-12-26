#ifndef HUMANLOADER_P_H
#define HUMANLOADER_P_H

#include <QThread>

#include "humanloader.h"
#include "humaninfo.h"

#include <QSqlQuery>


class HumanLoader_P : public QThread
{
    Q_OBJECT
    friend class HumanLoader;


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

    explicit HumanLoader_P( HumanLoader *parent );
    ~HumanLoader_P();

    HumanLoader * p_dptr() const;

    HumanInfo * newInfo();
};

#endif // HUMANLOADER_P_H
