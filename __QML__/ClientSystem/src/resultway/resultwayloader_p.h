#ifndef RESULTWAYLOADER_P_H
#define RESULTWAYLOADER_P_H

#include <QThread>

#include "resultwayloader.h"
#include "resultwayinfo.h"

#include <QSqlQuery>


class ResultwayLoader_P : public QThread
{
    Q_OBJECT
    friend class ResultwayLoader;


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

    explicit ResultwayLoader_P( ResultwayLoader *parent );
    ~ResultwayLoader_P();

    ResultwayLoader * p_dptr() const;

    ResultwayInfo * newInfo();
};

#endif // RESULTWAYLOADER_P_H
